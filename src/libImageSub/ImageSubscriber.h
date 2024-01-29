// Copyright 2019 Proyectos y Sistemas de Mantenimiento SL (eProsima).
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

#ifndef IMAGESUBSCRIBER_H_
#define IMAGESUBSCRIBER_H_

#include "libMsg/ImagePubSubTypes.h"
#include "libCfg/Cfg.h"

#include <fastdds/dds/domain/DomainParticipant.hpp>
#include <fastdds/dds/subscriber/DataReaderListener.hpp>
#include <fastrtps/subscriber/SampleInfo.h>
#include <fastdds/dds/core/status/SubscriptionMatchedStatus.hpp>
#include <fastdds/dds/domain/DomainParticipantListener.hpp>

#include <boost/filesystem.hpp>
#include "libUtil/Util.h"

using namespace eprosima::fastdds::dds;
class ImageSubscriber {
public:
  
    ImageSubscriber(app::CfgPtr cfg);

    virtual ~ImageSubscriber();

    //!Initialize the subscriber
    bool init(
            bool use_env);

    //!RUN the subscriber
    void run();

private:

    eprosima::fastdds::dds::DomainParticipant* participant_;

    eprosima::fastdds::dds::Subscriber* subscriber_;

    eprosima::fastdds::dds::Topic* topic_;

    eprosima::fastdds::dds::DataReader* reader_;

    eprosima::fastdds::dds::TypeSupport type_;

    eprosima::fastdds::dds::StatusMask p_mask_;

    class SubListener : public eprosima::fastdds::dds::DataReaderListener
    {
    public:

        SubListener(app::CfgPtr cfg)
            : matched_(0)
            , file_(std::ofstream())
            , frequency_(cfg->getCam().frequency_.start)
            , cfg_(cfg)
        {
            boost::filesystem::path dir("logs");

            if (!boost::filesystem::exists(dir)) {
                std::cout << "logs folder doesn't Exist" << std::endl;

                if (boost::filesystem::create_directory(dir)) {
                    std::cout << "Successfully created logs folder" << std::endl;
                }
                else {
                    std::cout << "Could not create logs folder." << std::endl;
                }
            }

            // https://stackoverflow.com/questions/38034033/c-localtime-this-function-or-variable-may-be-unsafe
            time_t t = std::time(nullptr);

            std::tm bt{};
            #if defined(__unix__)
                localtime_r(&t, &bt);
            #elif defined(_MSC_VER)
                localtime_s(&bt, &t);
            #else
                static std::mutex mtx;
                std::lock_guard<std::mutex> lock(mtx);
                bt = *std::localtime(&t);
            #endif

            startTime << std::put_time(&bt, "%Y%m%d%H%M%S");

            std::string folderName = "logs/" + startTime.str();
            if (boost::filesystem::create_directory(folderName)) {
                std::cout << "Successfully created " << folderName << " folder" << std::endl;
            }
            else {
                std::cout << "Could not create " << folderName << " folder." << std::endl;
            }

            createNewLogFile();
        }

        ~SubListener() override
        {
        }

        void on_data_available(
            eprosima::fastdds::dds::DataReader* reader) override;

        void on_subscription_matched(
            eprosima::fastdds::dds::DataReader* reader,
            const eprosima::fastdds::dds::SubscriptionMatchedStatus& info) override;

        void createNewLogFile() {
            std::string height = std::to_string(cfg_->getCam().imgSz_.h);
            std::string width = std::to_string(cfg_->getCam().imgSz_.w);
            std::string transport = TransportNames[cfg_->getTransport() - 1];
            std::string frequency = std::to_string(frequency_);

            std::stringstream fileName;
            fileName << transport << "_" << frequency_ << "_" << height << "_" << width;
            std::string outPutFile = "logs/" + startTime.str() + "/image_" + fileName.str() + ".csv";

            file_ = std::ofstream();
            file_.open(outPutFile, std::ofstream::out | std::ofstream::trunc);
            std::cout << "Opened " + outPutFile + " ..appending to file" << std::endl;
            file_ << "frame number,publisher_sent,subscriber_received,latency" << std::endl;
        }

        app::CfgPtr  cfg_;

        Image image_;

        int matched_;

        std::stringstream startTime;

        std::ofstream file_;

        int frequency_;

        app::AppMeanStd<uint32_t> latencyStat_;
    } listener_;

    app::CfgPtr  cfg_;

   // eprosima::fastdds::dds::TypeSupport type_;
};

void createImageSubscriber(app::CfgPtr cfg, bool use_environment_qos);

#endif /* IMAGESUBSCRIBER_H_ */
