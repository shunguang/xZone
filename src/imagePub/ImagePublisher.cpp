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
#include <fastdds/dds/domain/DomainParticipantFactory.hpp>
#include <fastdds/rtps/transport/TCPv4TransportDescriptor.h>
#include <fastdds/rtps/transport/UDPv4TransportDescriptor.h>
#include <fastdds/rtps/transport/shared_mem/SharedMemTransportDescriptor.h>
// #include <fastdds/rtps/attributes/ThreadSettings.hpp>

#include <fastrtps/utils/IPLocator.h>
#include <fastdds/dds/publisher/Publisher.hpp>
#include <fastdds/dds/publisher/qos/DataWriterQos.hpp>

#include <thread>
#include <chrono>
#include <list>

#include <iostream>

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
        case 1: {
           std::cout << "Using TCP as transport" << std::endl;
           std::shared_ptr<TCPv4TransportDescriptor> descriptor = std::make_shared<TCPv4TransportDescriptor>();
           descriptor->sendBufferSize = 0;
           descriptor->receiveBufferSize = 0;

            participant_qos.wire_protocol().builtin.discovery_config.leaseDuration = eprosima::fastrtps::c_TimeInfinite;
            // 0 seconds and 2e7 (20,000,000) nanoseconds or 20 miliseconds
            // this basically is how long should i wait until i should match with the publisher
            participant_qos.wire_protocol().builtin.discovery_config.leaseDuration_announcementperiod = eprosima::fastrtps::Duration_t(0, 2e7);
            descriptor->add_listener_port(5100);

            participant_qos.transport().user_transports.push_back(descriptor);
            participant_qos.transport().use_builtin_transports = false;

            break;
        }
        case 2: {
            std::cout << "Using UDP as transport" << std::endl;
            std::shared_ptr<UDPv4TransportDescriptor> descriptor = std::make_shared<UDPv4TransportDescriptor>();
 
            // Link the Transport Layer to the Participant.
            participant_qos.transport().user_transports.push_back(descriptor);
            participant_qos.transport().use_builtin_transports = false;
            break;
        }
        case 3: {
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
    wqos.history().depth = 30;
    wqos.resource_limits().max_samples = 50;
    wqos.resource_limits().allocated_samples = 20;
    wqos.reliable_writer_qos().times.heartbeatPeriod.seconds = 2;
    wqos.reliable_writer_qos().times.heartbeatPeriod.nanosec = 200 * 1000 * 1000;
    wqos.reliability().kind = RELIABLE_RELIABILITY_QOS;

    writer_ = publisher_->create_datawriter(topic_, wqos, &listener_);

    if (writer_ == nullptr)
    {
        return false;
    }
    // std::cout << "create_datawriter " << &image_.frame_number() << std::endl;
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

 void ImagePublisher::runThread(int &frame_number)
{
     // create a queue of integer data type
    const int numSamples = cfgPtr_->getCam().numSamples_;
    uint64_t tBeg = APP_TIME_CURRENT_NS;
    uint64_t tEnd = APP_TIME_CURRENT_NS;

    std::cout << "sending " << numSamples << " samples at " << frequency_ << std::endl;
    for (uint32_t sample_num = 0; sample_num < numSamples; sample_num++) {
        acqImgMsg();
        preparImgMsg(frame_number);

        tEnd = APP_TIME_CURRENT_NS;

        uint64_t dealayNanosecond = 1e9 / frequency_;
        // std::cout << "**dealayNanosecond " << dealayNanosecond  << std::endl;
         
       // wait utill delay time, interval
    
        while (tEnd - tBeg <= dealayNanosecond) {
            tEnd = APP_TIME_CURRENT_NS;
           //uncomment this line to test if a delay is needed
           // std::cout << "**in while loop " << std::endl;
        }
       
        if (!publish(false, numSamples)) {
            std::cout << "unable to send sample #" << sample_num << std::endl;
        }
        frame_number++;

        tBeg = APP_TIME_CURRENT_NS;
      }
}

std::thread ImagePublisher::run(int &frame_number)
{
    stop_ = false;
    std::thread thread(&ImagePublisher::runThread, this, std::ref(frame_number));
    return thread;
}

/*
void ImagePublisher::runThread(int i)
{
	acqImgMsg();
	preparImgMsg(i);

           // todo: make this thread
        if (!publish(false, cfgCam_.numSamples_)) {
            std::cout << "unable to send sample #" << i << std::endl;
        }
    }
    //std::cout << " published. " << i << std::endl;
}


std::thread ImagePublisher::run(int i)
{
    stop_ = false;
    std::thread thread(&ImagePublisher::runThread, this, i);
    return thread;
}
*/

void ImagePublisher::acqImgMsg()
{
  // https://learnopencv.com/read-write-and-display-a-video-using-opencv-cpp-python/
  image_.subscriber_initalize_time(APP_TIME_CURRENT_NS);
}

void ImagePublisher::preparImgMsg( const uint32_t frameNum )
{
  image_.frame_number(frameNum);
  image_.frequency(frequency_);
  image_.image(app::matToVecUchar(frame_));
  image_.width(frame_.cols);
  image_.height(frame_.rows);
  image_.transport(cfgPtr_->getTransport());
}

bool ImagePublisher::publish(bool waitForListener, uint32_t frequency)
//bool ImagePublisher::publish(bool waitForListener, uint32_t frequency, Image oneImage)
{
    if (listener_.firstConnected_ || !waitForListener || listener_.matched_ > 0)
    {
     //   std::cout << "is listener connected " << listener_.firstConnected_ << std::endl;
        //std::cout << "in publish frequency " << frequency << std::endl;
        image_.publisher_send_time(APP_TIME_CURRENT_NS);
        writer_->write(&image_);
        return true;
    }
    return false;
}
