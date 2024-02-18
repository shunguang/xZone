// Copyright 2016 Proyectos y Sistemas de Mantenimiento SL (eProsima).
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include "ImagePublisher.h"
#include "libUtil/AppDefs.h"

#include <fastdds/dds/domain/DomainParticipantFactory.hpp>
#include <fastdds/rtps/transport/TCPv4TransportDescriptor.h>
#include <fastdds/rtps/transport/UDPv4TransportDescriptor.h>
#include <fastdds/rtps/transport/shared_mem/SharedMemTransportDescriptor.h>
#include <fastrtps/utils/IPLocator.h>
#include <fastdds/dds/publisher/Publisher.hpp>
#include <fastdds/dds/publisher/qos/DataWriterQos.hpp>

#include <thread>
#include <chrono>
#include <list>
#include <iostream>

#include <opencv2/core/core.hpp>

using namespace eprosima::fastdds::dds;
using namespace eprosima::fastdds::rtps;

ImagePublisher::ImagePublisher(std::shared_ptr<std::shared_mutex> mutexPtr, CfgPtr cfgPtr, uint32_t fps)
    : participant_(nullptr)
    , publisher_(nullptr)
    , topic_(nullptr)
    , writer_(nullptr)
    , type_(new ImagePubSubType())
    , stop_(false)
{
    // what does this do
    //type_ = std::dynamic_pointer_cast<eprosima::fastdds::dds::TypeSupport>(std::shared_ptr<ImagePubSubType>());
    std::cout << "type_: " << type_ << std::endl;

    cfgPtr_ = cfgPtr;
    mutexPtr_ = mutexPtr;

    int height = cfgPtr->getCam().imgSz_.h;
    int width = cfgPtr->getCam().imgSz_.w;

    // there are 24 bits in a pixel using CV_8UC3 (3 bytes)
    frame_ = cv::Mat(height, width, CV_8UC3);

    // set publisher frequency
    frequency_ = fps;

   // https://learnopencv.com/read-write-and-display-a-video-using-opencv-cpp-python/
   // https://learn.microsoft.com/en-us/windows/win32/directshow/selecting-a-capture-device?redirectedfrom=MSDN
   // command to list available video and audio devices
   // ffmpeg -list_devices true -f dshow -i dummy
   //camera_ = cv::VideoCapture(0, cv::CAP_DSHOW);
   // //// Check if camera opened successfully
   // if (!camera_.isOpened()) {
   //     std::cout << "[ImagePublisher] constructor: Error opening video stream or file" << std::endl;
   // }

   // // set the camera configuration
   // // https://docs.opencv.org/3.4/d4/d15/group__videoio__flags__base.html#gaeb8dd9c89c10a5c63c139bf7c4f5704d
   // // "Effective behaviour depends from device hardware, driver and API Backend."
   // camera_.set(cv::CAP_PROP_FRAME_HEIGHT, cfgCamPtr->imgSz_.w);
   // camera_.set(cv::CAP_PROP_FRAME_WIDTH, cfgCamPtr->imgSz_.h);
   // camera_.set(cv::CAP_PROP_FPS, cfgCamPtr->fps_.getFps());
}

bool ImagePublisher::init(CfgPtr cfg, bool use_env)
{
    image_.frame_number(0);
    
    DomainParticipantQos participant_qos = PARTICIPANT_QOS_DEFAULT;
    participant_qos.name("ImagePublisher");

    PublishModeQosPolicy publish_mode;
     
    auto factory = DomainParticipantFactory::get_instance();

    if (factory == NULL) {
        // ... error
    }
    if (use_env)
    {
        factory->load_profiles();
        factory->get_default_participant_qos(participant_qos);
    }
    stop_ = false;
  
    switch (cfg->getTransport()) {
        case Transport::TCP: {
                std::cout << "Using TCP as transport" << std::endl;
                std::shared_ptr<TCPv4TransportDescriptor> descriptor = std::make_shared<TCPv4TransportDescriptor>();
                descriptor->sendBufferSize = 0;
                descriptor->receiveBufferSize = 0;
                //descriptor->enable_tcp_nodelay = true;

                participant_qos.wire_protocol().builtin.discovery_config.leaseDuration = eprosima::fastrtps::c_TimeInfinite;
                // 0 seconds and 2e7 (20,000,000) nanoseconds or 20 miliseconds
                // this basically is how long should i wait until i should match with the publisher
                participant_qos.wire_protocol().builtin.discovery_config.leaseDuration_announcementperiod = eprosima::fastrtps::Duration_t(0, 1);
                descriptor->add_listener_port(5100);

                participant_qos.transport().user_transports.push_back(descriptor);
                participant_qos.transport().use_builtin_transports = false;

                break;
        }
        case Transport::UDP: {
                std::cout << "Using UDP as transport" << std::endl;
                std::shared_ptr<UDPv4TransportDescriptor> descriptor = std::make_shared<UDPv4TransportDescriptor>();
 
                // Link the Transport Layer to the Participant.
                participant_qos.transport().user_transports.push_back(descriptor);
                participant_qos.transport().use_builtin_transports = false;
                break;
        }
        case Transport::SharedMemory: {
            std::cout << "Using Shared memory as transport" << std::endl;

            // Create a descriptor for the new transport.
            std::shared_ptr<SharedMemTransportDescriptor> descriptor = std::make_shared<SharedMemTransportDescriptor>();

            // Link the Transport Layer to the Participant.
            participant_qos.transport().user_transports.push_back(descriptor);
            participant_qos.transport().use_builtin_transports = false;
            break;
        }
        default: {
            std::cout << "Using FastDDS Default transport (UDP)" << std::endl;
        }
    }

    participant_ = DomainParticipantFactory::get_instance()->create_participant(0, participant_qos);

    if (participant_ == nullptr)
    {
        return false;
    }

    type_.register_type(participant_);

    PublisherQos pubqos = PUBLISHER_QOS_DEFAULT;
  
    publisher_ = participant_->create_publisher(
        pubqos,
        nullptr);
    publisher_->wait_for_acknowledgments(eprosima::fastrtps::c_TimeInfinite);

    if (publisher_ == nullptr)
    {
        return false;
    }

    topic_ = participant_->create_topic(
        "ImageTopic",
        "Image", TOPIC_QOS_DEFAULT);

    if (topic_ == nullptr)
    {
        return false;
    }

    DataWriterQos wqos = DATAWRITER_QOS_DEFAULT;

    if (false)
    {
        publisher_->get_default_datawriter_qos(wqos);
    }
    
    wqos.history().kind = KEEP_LAST_HISTORY_QOS;
    wqos.history().depth = 1;
    wqos.resource_limits().max_samples = 1;
    wqos.resource_limits().allocated_samples = 1;
    wqos.reliable_writer_qos().times.heartbeatPeriod.seconds = 2;
    wqos.reliable_writer_qos().times.heartbeatPeriod.nanosec = 200 * 1000 * 1000;
    wqos.reliability().kind = BEST_EFFORT_RELIABILITY_QOS;

    writer_ = publisher_->create_datawriter(topic_, wqos, &listener_);

    if (writer_ == nullptr)
    {
        return false;
    }

    return true;
}

ImagePublisher::~ImagePublisher()
{
    if (writer_ != nullptr)
    {
        publisher_->delete_datawriter(writer_);
       // std::cout << "delete_datawriter." << std::endl;
    }
    if (publisher_ != nullptr)
    {
        participant_->delete_publisher(publisher_);

       // std::cout << "delete_publisher." << std::endl;
    }
    if (topic_ != nullptr)
    {
        participant_->delete_topic(topic_);
    }
   
    //delete type_.get();
    DomainParticipantFactory::get_instance()->delete_participant(participant_);

   // std::cout << "delete_participant." << std::endl;

}

void ImagePublisher::PubListener::on_offered_deadline_missed(
    DataWriter* writer,
    const eprosima::fastdds::dds::OfferedDeadlineMissedStatus& status)
{
    static_cast<void>(writer);
    static_cast<void>(status);
    std::cout << "Some data could not be delivered on time" << std::endl;
}

void ImagePublisher::PubListener::on_offered_incompatible_qos(
    eprosima::fastdds::dds::DataWriter* writer,
    const eprosima::fastdds::dds::OfferedIncompatibleQosStatus& status)
{
    std::cout << "Found a remote Topic with incompatible QoS (QoS ID: " << status.last_policy_id <<
        ")" << std::endl;
}

void ImagePublisher::PubListener::on_liveliness_lost(
    eprosima::fastdds::dds::DataWriter* writer,
    const eprosima::fastdds::dds::LivelinessLostStatus& status)
{
    static_cast<void>(writer);
    static_cast<void>(status);
    std::cout << "Liveliness lost. Matched Subscribers will consider us offline" << std::endl;
}

void ImagePublisher::PubListener::on_unacknowledged_sample_removed(
    eprosima::fastdds::dds::DataWriter* writer,
    const eprosima::fastdds::dds::InstanceHandle_t& instance)
{
    static_cast<void>(writer);
    static_cast<void>(instance);
    // std::cout << "Sample removed unacknowledged" << std::endl;
}

void ImagePublisher::PubListener::on_publication_matched(
        eprosima::fastdds::dds::DataWriter*,
        const eprosima::fastdds::dds::PublicationMatchedStatus& info)
{
    if (info.current_count_change == 1)
    {
        matched_ = info.total_count;
        firstConnected_ = true;
        std::cout << "Publisher matched." << std::endl;
    }
    else if (info.current_count_change == -1)
    {
        matched_ = info.total_count;
        std::cout << "Publisher unmatched." << std::endl;
    }
    else
    {
        std::cout << info.current_count_change
                  << " is not a valid value for PublicationMatchedStatus current count change" << std::endl;
    }
}

void ImagePublisher::runPacketSizeVariable(int max_packet_size) {
    const int numSamples = cfgPtr_->getCam().numSamples_;
    uint64_t tBeg = APP_TIME_CURRENT_US;
    uint64_t tEnd = APP_TIME_CURRENT_US;
    
    int frame_number = 1;
    cv::Size size = cv::Size(1, 1);
    std::cout << "area: " << size.area() * 3 << " pckt size: " << max_packet_size << std::endl;
    while (size.area() * 3 <= max_packet_size) {
        frame_ = cv::Mat(size, CV_8UC3);
        
        for (uint32_t sample_num = 0; sample_num < numSamples; sample_num++) {
            acqImgMsg();
            preparImgMsg(frame_number);

            if (!publish(false, numSamples)) {
                std::cout << "unable to send frame number #" << frame_number << std::endl;
            }
        }

        frame_number++;
        size = cv::Size(1, size.height + 1);

        tBeg = APP_TIME_CURRENT_US;
    }
}

 void ImagePublisher::runFrequency(int &frame_number)
{
    const int numSamples = cfgPtr_->getCam().numSamples_;
    uint64_t delayMacrosecond = 1e6 / frequency_;
    uint64_t tBeg = APP_TIME_CURRENT_US;
    uint64_t tEnd = APP_TIME_CURRENT_US;

    std::cout << "sending " << numSamples << " samples at " << frequency_ << std::endl;
    for (int sample_num = 0; sample_num < numSamples; sample_num++) {
        tBeg = APP_TIME_CURRENT_US;

        preparImgMsg(frame_number);
        acqImgMsg();

        if (!publish(false, sample_num)) {
            std::cout << "unable to send sample #" << sample_num << std::endl;
        }

        tEnd = APP_TIME_CURRENT_US;
        
        APP_SLEEP2(delayMacrosecond);

        frame_number++;        
    }
     
}

void ImagePublisher::acqImgMsg()
{
    //image_.frame_number();
  // https://learnopencv.com/read-write-and-display-a-video-using-opencv-cpp-python/
  image_.publisher_acq_time(APP_TIME_CURRENT_US);
}

void ImagePublisher::preparImgMsg( const int frameNum )
{
  image_.frame_number(frameNum);
  image_.image(app::matToVecUchar(frame_));
  image_.width(frame_.cols);
  image_.height(frame_.rows);
}

bool ImagePublisher::publish(bool waitForListener, int sampleNum)
{
    if (listener_.firstConnected_ || !waitForListener || listener_.matched_ > 0)
    {
        image_.publisher_send_time(APP_TIME_CURRENT_US);
        writer_->write(&image_);

        if (cfgPtr_->getCam().numSamples_ - 1 == sampleNum) {
            image_.frame_number(std::numeric_limits<uint32_t>().max());
            writer_->write(&image_);
        }
        return true;       
    }
    return false;
}
