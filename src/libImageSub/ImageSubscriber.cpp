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

#include "ImageSubscriber.h"
#include "UpdateCamPublisher.h"
#include <fastrtps/attributes/ParticipantAttributes.h>
#include <fastrtps/attributes/SubscriberAttributes.h>
#include <fastdds/dds/domain/DomainParticipantFactory.hpp>
#include <fastdds/dds/subscriber/Subscriber.hpp>
#include <fastdds/dds/subscriber/DataReader.hpp>
#include <fastdds/dds/subscriber/SampleInfo.hpp>
#include <fastdds/dds/subscriber/qos/DataReaderQos.hpp>
#include <fastdds/rtps/transport/UDPv4TransportDescriptor.h>
#include <fastdds/rtps/transport/TCPv4TransportDescriptor.h>
#include <fastdds/rtps/transport/shared_mem/SharedMemTransportDescriptor.h>
#include <fastrtps/utils/IPLocator.h>


using namespace eprosima::fastdds::rtps;
using namespace eprosima::fastdds::dds;
using namespace app;

using IPLocator = eprosima::fastrtps::rtps::IPLocator;

ImageSubscriber::ImageSubscriber()
    : participant_(nullptr)
    , subscriber_(nullptr)
    , topic_(nullptr)
    , reader_(nullptr)
    , type_(new ImagePubSubType())
{
}

bool ImageSubscriber::init(
        CfgPtr  cfg,
        bool use_env)
{
    DomainParticipantQos pqos = PARTICIPANT_QOS_DEFAULT;
    pqos.name("ImageSubscriber");
    DomainParticipantFactory* factory = DomainParticipantFactory::get_instance();

    if (use_env)
    {
        factory->load_profiles();
        factory->get_default_participant_qos(pqos);
    }

    // Set initial peers.
    // std::cout << "Using TCP as transport " << cfg->getTransport()  << std::endl;

    switch (cfg->getTransport()) {

    case 1: {
        std::cout << "Using TCP as transport" << std::endl;

        // client
        pqos.transport().use_builtin_transports = false;

        // Create a descriptor for the new transport.
        // Do not configure any listener port
        auto tcp_transport = std::make_shared<TCPv4TransportDescriptor>();
        pqos.transport().user_transports.push_back(tcp_transport);

        eprosima::fastrtps::rtps::Locator_t initial_peer_locator;
        initial_peer_locator.kind = LOCATOR_KIND_TCPv4;
        IPLocator::setIPv4(initial_peer_locator, "127.0.0.1");
        initial_peer_locator.port = 5100;
        pqos.wire_protocol().builtin.initialPeersList.push_back(initial_peer_locator);

        pqos.wire_protocol().builtin.discovery_config.leaseDuration = eprosima::fastrtps::c_TimeInfinite;
        pqos.wire_protocol().builtin.discovery_config.leaseDuration_announcementperiod = Duration_t(0, 2e7);
        //IPLocator::setPhysicalPort(initial_peer_locator, 5100);
        //IPLocator::setLogicalPort(initial_peer_locator, 5100);

        //pqos.wire_protocol().builtin.discovery_config.leaseDuration = eprosima::fastrtps::c_TimeInfinite;
        //pqos.wire_protocol().builtin.discovery_config.leaseDuration_announcementperiod = Duration_t(5, 0);

        pqos.transport().use_builtin_transports = false;
      /*  pqos.wire_protocol().builtin.initialPeersList.push_back(initial_peer_locator);*/
        break;
    }
    case 2: {
        std::cout << "Using UDP as transport" << std::endl;

        auto udp_transport = std::make_shared<UDPv4TransportDescriptor>();
        udp_transport->non_blocking_send = true;

        // Link the Transport Layer to the Participant.
        pqos.transport().user_transports.push_back(udp_transport);

        // Avoid using the default transport
        pqos.transport().use_builtin_transports = false;
        break;
    }
    case 3: {
        std::cout << "Using Shared Memory as transport" << std::endl;

        // Create a descriptor for the new transport.
        std::shared_ptr<SharedMemTransportDescriptor> shm_transport = std::make_shared<SharedMemTransportDescriptor>();

        // Link the Transport Layer to the Participant.
        pqos.transport().user_transports.push_back(shm_transport);

        pqos.transport().use_builtin_transports = false;
        break;
    }
    default: {
        
    }
    }
   
    participant_ = factory->create_participant(0, pqos);
    // std::cout << "Domain Id: " << participant_->get_domain_id() << std::endl;

   // participant_ = factory->create_participant(0, pqos);

    if (participant_ == nullptr)
    {
        std::cout << " in if participant_ == nullptr" << std::endl;
        return false;
    }

    //REGISTER THE TYPE
    type_.register_type(participant_);

    //CREATE THE SUBSCRIBER
    SubscriberQos sqos = SUBSCRIBER_QOS_DEFAULT;

    /*
    if (use_env)
    {
        participant_->get_default_subscriber_qos(sqos);
    }

    subscriber_ = participant_->create_subscriber(sqos, nullptr);
    */

    if (use_env)
    {
        //subscriber_->get_default_datareader_qos(rqos);
    }
    else {
        //CREATE THE SUBSCRIBER
        subscriber_ = participant_->create_subscriber(SUBSCRIBER_QOS_DEFAULT);
    }
  

    if (subscriber_ == nullptr)
    {
        return false;
    }
    std::cout << "create_subscriber" << std::endl;

    //CREATE THE TOPIC
    TopicQos tqos = TOPIC_QOS_DEFAULT;

  
    /*
      if (use_env)
    {
        participant_->get_default_topic_qos(tqos);
    }
    */

    topic_ = participant_->create_topic(
        "ImageTopic",
        "Image",
        tqos);
    std::cout << "create_topic" << std::endl;
    if (topic_ == nullptr)
    {
        return false;
    }

    //CREATE THE DATAREADER

    DataReaderQos rqos;
    rqos.history().kind = eprosima::fastdds::dds::KEEP_LAST_HISTORY_QOS;
    rqos.history().depth = 30;
    rqos.resource_limits().max_samples = 50;
    rqos.resource_limits().allocated_samples = 20;
    rqos.reliability().kind = eprosima::fastdds::dds::RELIABLE_RELIABILITY_QOS;
    rqos.durability().kind = eprosima::fastdds::dds::TRANSIENT_LOCAL_DURABILITY_QOS;
    reader_ = subscriber_->create_datareader(topic_, rqos, &listener_);

 //   DataReaderQos rqos;
  //     rqos.history().kind = eprosima::fastdds::dds::KEEP_LAST_HISTORY_QOS;
 //   rqos.history().depth = 30;
 //   rqos.resource_limits().max_samples = 50;
  //  rqos.resource_limits().allocated_samples = 20;
   // rqos.reliability().kind = eprosima::fastdds::dds::RELIABLE_RELIABILITY_QOS;
    //rqos.durability().kind = eprosima::fastdds::dds::TRANSIENT_LOCAL_DURABILITY_QOS;

    reader_ = subscriber_->create_datareader(topic_, rqos, &listener_, StatusMask::all());

    if (reader_ == nullptr)
    {
        return false;
    }
    std::cout << "create_datareader" << std::endl;
    return true;
}

ImageSubscriber::~ImageSubscriber()
{
   
    if (reader_ != nullptr)
    {
        subscriber_->delete_datareader(reader_);
    }
    if (topic_ != nullptr)
    {
        participant_->delete_topic(topic_);
    }
    if (subscriber_ != nullptr)
    {
        participant_->delete_subscriber(subscriber_);
    }
    DomainParticipantFactory::get_instance()->delete_participant(participant_);
}

void ImageSubscriber::SubListener::on_subscription_matched(
        DataReader*,
        const SubscriptionMatchedStatus& info)
{
    if (info.current_count_change == 1)
    {
        matched_ = info.total_count;
        std::cout << "Subscriber matched." << matched_ << std::endl;

      //  std::thread updateCamPublisher(createUpdateCamPublisher, false);
      //  updateCamPublisher.join();
    }
    else if (info.current_count_change == -1)
    {
        matched_ = info.total_count;
        std::cout << "Subscriber unmatched." << matched_ << std::endl;

        //file_.close();
        //std::terminate();
    }
    else
    {
        std::cout << info.current_count_change
                  << " is not a valid value for SubscriptionMatchedStatus current count change" << std::endl;
    }
}

void ImageSubscriber::SubListener::on_data_available(  DataReader* reader)
{
    SampleInfo info;

    if (reader->take_next_sample(&image_, &info) == ReturnCode_t::RETCODE_OK)
    {
        if (info.instance_state == ALIVE_INSTANCE_STATE)
        {
            samples_++;
            // Print your structure data here.

            //while (1) {

            //    cv::Mat frame;
            //    frame = app::vecUcharToMat(image_.image(), image_.width(), image_.height());

            //    // Display the resulting frame
            //    cv::imshow("Frame", frame);

            //    // Press  ESC on keyboard to exit
            //    char c = (char) cv::waitKey(25);
            //    if (c == 27)
            //        break;
            //}

            //APP_LOG("frame number=%u received, time captured (t1)=%u, time sent msg out (t2)=%u, time received msg (t3)=%u", image_.frame_number(), image_.t1(), image_.t2(), APP_TIME_CURRENT_NS);

            // write data to data.csv file 
            // frame number, frequency, latency

           
            image_.subscriber_recieve_time(APP_TIME_CURRENT_NS);
            //if (image_.frame_number() > 100) {
                latencyStat_.addSample(image_.subscriber_recieve_time() - image_.publisher_send_time());
            //}
                
            file_ << image_.frame_number() << ","  << image_.height() << "," << image_.width() << "," << image_.publisher_send_time() << "," << image_.subscriber_recieve_time() << "," << image_.frequency() << "," << image_.subscriber_recieve_time() - image_.publisher_send_time() << "," << samples_ << "," << image_.transport() << std::endl;
           // output_data_stringstream_ << image_.frame_number() << "," << image_.height() << "," << image_.width() 
           //         << "," << image_.publisher_send_time() << "," << image_.subscriber_recieve_time() << "," << image_.frequency() 
           //         << "," << image_.subscriber_recieve_time() - image_.publisher_send_time() << "," << samples_ << std::endl;
        }
    }
}

void ImageSubscriber::run()
{
  APP_LOG("subscriber running. Please press enter to stop the Subscriber");
  std::cin.ignore();
}

void ImageSubscriber::run(uint32_t number)
{
    std::cout << "Subscriber running until " << number << "samples have been received" << std::endl;
    while (number > listener_.samples_)
    {
      APP_LOG("HelloWorldSubscriber::run(): sleep 500 ms");
      std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }
}

void createImageSubscriber(CfgPtr cfg, bool use_environment_qos) {
    ImageSubscriber imageSubscriber;
    if (imageSubscriber.init(cfg, use_environment_qos)) imageSubscriber.run();
}
