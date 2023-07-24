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

#ifndef TEMPERATUREPUBLISHER_H_
#define TEMPERATUREPUBLISHER_H_

#include "libUtil/Util.h"
#include "libMsg/TemperaturePubSubTypes.h"
#include "libCfg/Cfg.h"

#include <fastdds/dds/publisher/DataWriterListener.hpp>
#include <fastdds/dds/topic/TypeSupport.hpp>
#include <fastdds/dds/domain/DomainParticipant.hpp>

#include <mutex>
#include <shared_mutex>

using namespace app;

class TemperaturePublisher
{
public:

    TemperaturePublisher(std::shared_ptr<std::shared_mutex> mutex, CfgThermometerPtr cfgThermometerPtr);

    virtual ~TemperaturePublisher();

    //!Initialize
    bool init(
        bool use_env);

    //!Publish a sample
    bool publish(
        bool waitForListener = true);

    //!Run for number samples
    std::thread run(
        uint32_t number,
        uint32_t sleep);

private:

    CfgThermometerPtr cfgThermometerPtr_;

    std::shared_ptr<std::shared_mutex> mutexPtr_;

    Temperature temperature_;

    eprosima::fastdds::dds::DomainParticipant* participant_;

    eprosima::fastdds::dds::Publisher* publisher_;

    eprosima::fastdds::dds::Topic* topic_;

    eprosima::fastdds::dds::DataWriter* writer_;

    bool stop_;

    class PubListener : public eprosima::fastdds::dds::DataWriterListener
    {
    public:

        PubListener()
            : matched_(0)
            , firstConnected_(false)
        {
        }

        ~PubListener() override
        {
        }

        void on_publication_matched(
            eprosima::fastdds::dds::DataWriter* writer,
            const eprosima::fastdds::dds::PublicationMatchedStatus& info) override;

        int matched_;

        bool firstConnected_;
    }
    listener_;

    void runThread(
        uint32_t number,
        uint32_t sleep);

    eprosima::fastdds::dds::TypeSupport type_;
};

#endif
