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
#include <libUtil/FileUtil.h>
#include "opencv2/opencv.hpp"
#include <fastrtps/attributes/ParticipantAttributes.h>
#include <fastrtps/attributes/PublisherAttributes.h>
#include <fastdds/dds/domain/DomainParticipantFactory.hpp>
#include <fastdds/dds/publisher/Publisher.hpp>
#include <fastdds/dds/publisher/qos/PublisherQos.hpp>
#include <fastdds/dds/publisher/DataWriter.hpp>
#include <fastdds/dds/publisher/qos/DataWriterQos.hpp>

#include <thread>
#include <iostream>

using namespace app;
using namespace eprosima::fastdds::dds;

ImagePublisher::ImagePublisher(std::shared_ptr<std::shared_mutex> mutexPtr, CfgCamPtr cfgCamPtr)
    : participant_(nullptr)
    , publisher_(nullptr)
    , topic_(nullptr)
    , writer_(nullptr)
    , type_(new ImagePubSubType())
    , stop_(false)
{

    cfgCamPtr_ = cfgCamPtr;
    mutexPtr_ = mutexPtr;

   // https://learnopencv.com/read-write-and-display-a-video-using-opencv-cpp-python/
   // https://learn.microsoft.com/en-us/windows/win32/directshow/selecting-a-capture-device?redirectedfrom=MSDN
   // command to list available video and audio devices
   // ffmpeg -list_devices true -f dshow -i dummy
   camera_ = cv::VideoCapture(0, cv::CAP_DSHOW);
    //// Check if camera opened successfully
    if (!camera_.isOpened()) {
        std::cout << "[ImagePublisher] constructor: Error opening video stream or file" << std::endl;
    }

    // set the camera configuration
    // https://docs.opencv.org/3.4/d4/d15/group__videoio__flags__base.html#gaeb8dd9c89c10a5c63c139bf7c4f5704d
    // "Effective behaviour depends from device hardware, driver and API Backend."
    camera_.set(cv::CAP_PROP_FRAME_HEIGHT, cfgCamPtr->imgSz_.w);
    camera_.set(cv::CAP_PROP_FRAME_WIDTH, cfgCamPtr->imgSz_.h);
    camera_.set(cv::CAP_PROP_FPS, cfgCamPtr->fps_.getFps());
}

bool ImagePublisher::init( bool use_env)
{

    image_.frame_number(0);

    DomainParticipantQos pqos = PARTICIPANT_QOS_DEFAULT;
    pqos.name("ImagePublisher");
    auto factory = DomainParticipantFactory::get_instance();

    if (use_env)
    {
        factory->load_profiles();
        factory->get_default_participant_qos(pqos);
    }

    participant_ = factory->create_participant(0, pqos);

    if (participant_ == nullptr)
    {
        return false;
    }

    //REGISTER THE TYPE
    type_.register_type(participant_);

    //CREATE THE PUBLISHER
    PublisherQos pubqos = PUBLISHER_QOS_DEFAULT;

    if (use_env)
    {
        participant_->get_default_publisher_qos(pubqos);
    }

    publisher_ = participant_->create_publisher(
        pubqos,
        nullptr);

    if (publisher_ == nullptr)
    {
        return false;
    }

    //CREATE THE TOPIC
    TopicQos tqos = TOPIC_QOS_DEFAULT;

    if (use_env)
    {
        participant_->get_default_topic_qos(tqos);
    }

    topic_ = participant_->create_topic(
        "ImageTopic",
        "Image",
        tqos);

    if (topic_ == nullptr)
    {
        return false;
    }

    // CREATE THE WRITER
    DataWriterQos wqos = DATAWRITER_QOS_DEFAULT;

    if (use_env)
    {
        publisher_->get_default_datawriter_qos(wqos);
    }

    writer_ = publisher_->create_datawriter(
        topic_,
        wqos,
        &listener_);

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
    }
    if (publisher_ != nullptr)
    {
        participant_->delete_publisher(publisher_);
    }
    if (topic_ != nullptr)
    {
        participant_->delete_topic(topic_);
    }
    DomainParticipantFactory::get_instance()->delete_participant(participant_);
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

void ImagePublisher::runThread()
{
    auto [start, step, end] = cfgCamPtr_->frequency_;

    for (uint32_t nSamples = start; nSamples < end; nSamples += step) {
        auto start = std::chrono::high_resolution_clock::now();
        std::cout << "sending " << nSamples << " samples" << std::endl;
        for (uint32_t i = 0; i < nSamples; i++) {
            if (publish(false, nSamples)) {
                //std::cout << " with index: " << image_.frame_number()
                //    << " SENT" << std::endl;
            }
        }

        // sleep until a second has passed
        std::chrono::duration<double> elapsed = std::chrono::high_resolution_clock::now() - start;
        // elapsed.count() is the amount of seconds that have elapsed
        if (elapsed.count() < 1) {
            std::cout << "sleeping for" << elapsed.count() << std::endl;
            std::this_thread::sleep_for(std::chrono::seconds((uint32_t) (1 - elapsed.count())));
            std::cout << "finished sleeping" << std::endl;
        }
    }
    std::cout << "finished sending samples" << std::endl;
}

std::thread ImagePublisher::run()
{
    stop_ = false;
    std::thread thread(&ImagePublisher::runThread, this);
    //if (samples == 0)
    //{
    //    std::cout << "Publisher running. Please press enter to stop the Publisher at any time." << std::endl;
    //    std::cin.ignore();
    //    stop_ = true;
    //}
    //else
    //{
       auto [start, step, end] = cfgCamPtr_->frequency_;
       // min: 10, step: 5, max: 100
       // Array.from({length: 19}, (e, i) => 10 + (i * 5)).reduce((a, b) => a + b)
       // sum of arithmetic sequence formula: Sn = (n/2)(a1+a2) to calculate the number of samples
       int iterations = ((end - start) / step) + 1;
      APP_LOG("Publisher will start at %u hertz step by %u and end at %u hertz, completing %u samples!", start, step, end, (iterations / 2) * (start + end));
    //}
    return thread;
}

bool ImagePublisher::publish( bool waitForListener, uint32_t frequency)
{
    if (listener_.firstConnected_ || !waitForListener || listener_.matched_ > 0)
    {
        // https://learnopencv.com/read-write-and-display-a-video-using-opencv-cpp-python/

        image_.t1(TS_SINCE_EPOCH_US);

        cv::Mat frame;
        camera_ >> frame;
        if (frame.empty()) {
            std::cout << "empty frame" << std::endl;
            return false;
        }

        image_.frame_number(image_.frame_number() + 1);
        image_.image(app::matToVecUchar(frame));
        image_.width(frame.cols);
        image_.height(frame.rows);
        image_.frequency(frequency);

        image_.t2(TS_SINCE_EPOCH_US);

        writer_->write(&image_);
        return true;
    }
    return false;
}