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

#include "HumidityPublisher.h"
#include <libUtil/AppDefs.h>
#include <libUtil/FileUtil.h>

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

HumidityPublisher::HumidityPublisher(std::shared_ptr<std::shared_mutex> mutexPtr, CfgHygrometerPtr cfgHygrometerPtr)
    : participant_(nullptr)
    , publisher_(nullptr)
    , topic_(nullptr)
    , writer_(nullptr)
    , type_(new HumidityPubSubType())
    , stop_(false)
{

    cfgHygrometerPtr_ = cfgHygrometerPtr;
    mutexPtr_ = mutexPtr;

    //// set the camera configuration
    //// https://docs.opencv.org/3.4/d4/d15/group__videoio__flags__base.html#gaeb8dd9c89c10a5c63c139bf7c4f5704d
    //// "Effective behaviour depends from device hardware, driver and API Backend."
    //camera_.set(cv::CAP_PROP_FRAME_HEIGHT, cfgCamPtr->imgSz_.w);
    //camera_.set(cv::CAP_PROP_FRAME_WIDTH, cfgCamPtr->imgSz_.h);
    //camera_.set(cv::CAP_PROP_FPS, cfgCamPtr->fps_.getFps());
}

bool HumidityPublisher::init(bool use_env)
{

    //image_.frame_number(0);

    DomainParticipantQos pqos = PARTICIPANT_QOS_DEFAULT;
    pqos.name("HumidityPublisher");
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

HumidityPublisher::~HumidityPublisher()
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

void HumidityPublisher::PubListener::on_publication_matched(
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

void HumidityPublisher::runThread(
    uint32_t samples,
    uint32_t sleep)
{
    auto [start, step, end] = cfgHygrometerPtr_->frequency_;

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
            std::this_thread::sleep_for(std::chrono::seconds((uint32_t)(1 - elapsed.count())));
            std::cout << "finished sleeping" << std::endl;
        }
    }
    std::cout << "finished sending samples" << std::endl;
}

std::thread HumidityPublisher::run(uint32_t samples, uint32_t sleep)
{
    stop_ = false;
    std::thread thread(&HumidityPublisher::runThread, this, samples, sleep);
    if (samples == 0)
    {
        std::cout << "Publisher running. Please press enter to stop the Publisher at any time." << std::endl;
        std::cin.ignore();
        stop_ = true;
    }
    else
    {
        APP_LOG("Publisher will run %d samples!", samples);
    }
    //thread.join();
    return thread;
}

bool HumidityPublisher::publish(bool waitForListener, uint32_t frequency)
{
    if (listener_.firstConnected_ || !waitForListener || listener_.matched_ > 0)
    {
        humidity_.subscriber_initalize_time(APP_TIME_CURRENT_NS);

        humidity_.humidity(5);

        humidity_.publisher_send_time(APP_TIME_CURRENT_NS);

        writer_->write(&humidity_);
        return true;
    }
    return false;
}
