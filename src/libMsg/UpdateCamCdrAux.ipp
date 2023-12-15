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

/*!
 * @file UpdateCamCdrAux.ipp
 * This source file contains some declarations of CDR related functions.
 *
 * This file was generated by the tool fastddsgen.
 */

#ifndef _FAST_DDS_GENERATED_UPDATECAMCDRAUX_IPP_
#define _FAST_DDS_GENERATED_UPDATECAMCDRAUX_IPP_

#include "UpdateCamCdrAux.hpp"

#include <fastcdr/Cdr.h>
#include <fastcdr/CdrSizeCalculator.hpp>


#include <fastcdr/exceptions/BadParamException.h>
using namespace eprosima::fastcdr::exception;

namespace eprosima {
namespace fastcdr {



template<>
eProsima_user_DllExport size_t calculate_serialized_size(
        eprosima::fastcdr::CdrSizeCalculator& calculator,
        const UpdateCam& data,
        size_t& current_alignment)
{
    static_cast<void>(data);

    eprosima::fastcdr::EncodingAlgorithmFlag previous_encoding = calculator.get_encoding();
    size_t calculated_size {calculator.begin_calculate_type_serialized_size(
                                eprosima::fastcdr::CdrVersion::XCDRv2 == calculator.get_cdr_version() ?
                                eprosima::fastcdr::EncodingAlgorithmFlag::DELIMIT_CDR2 :
                                eprosima::fastcdr::EncodingAlgorithmFlag::PLAIN_CDR,
                                current_alignment)};


        calculated_size += calculator.calculate_member_serialized_size(eprosima::fastcdr::MemberId(0),
                data.rtspUrl(), current_alignment);

        calculated_size += calculator.calculate_member_serialized_size(eprosima::fastcdr::MemberId(1),
                data.valid(), current_alignment);

        calculated_size += calculator.calculate_member_serialized_size(eprosima::fastcdr::MemberId(2),
                data.imgW(), current_alignment);

        calculated_size += calculator.calculate_member_serialized_size(eprosima::fastcdr::MemberId(3),
                data.imgH(), current_alignment);

        calculated_size += calculator.calculate_member_serialized_size(eprosima::fastcdr::MemberId(4),
                data.fpsNum(), current_alignment);

        calculated_size += calculator.calculate_member_serialized_size(eprosima::fastcdr::MemberId(5),
                data.fpsDen(), current_alignment);

        calculated_size += calculator.calculate_member_serialized_size(eprosima::fastcdr::MemberId(6),
                data.frmQueSz(), current_alignment);

        calculated_size += calculator.calculate_member_serialized_size(eprosima::fastcdr::MemberId(7),
                data.detPyrLev(), current_alignment);

        calculated_size += calculator.calculate_member_serialized_size(eprosima::fastcdr::MemberId(8),
                data.detMethodId(), current_alignment);

        calculated_size += calculator.calculate_member_serialized_size(eprosima::fastcdr::MemberId(9),
                data.detNetworkId(), current_alignment);

        calculated_size += calculator.calculate_member_serialized_size(eprosima::fastcdr::MemberId(10),
                data.detFrmsToSkip(), current_alignment);

        calculated_size += calculator.calculate_member_serialized_size(eprosima::fastcdr::MemberId(11),
                data.mp4LocationAndPrefix(), current_alignment);

        calculated_size += calculator.calculate_member_serialized_size(eprosima::fastcdr::MemberId(12),
                data.subscriber_initalize_time(), current_alignment);

        calculated_size += calculator.calculate_member_serialized_size(eprosima::fastcdr::MemberId(13),
                data.publisher_send_time(), current_alignment);

        calculated_size += calculator.calculate_member_serialized_size(eprosima::fastcdr::MemberId(14),
                data.subscriber_recieve_time(), current_alignment);


    calculated_size += calculator.end_calculate_type_serialized_size(previous_encoding, current_alignment);

    return calculated_size;
}

template<>
eProsima_user_DllExport void serialize(
        eprosima::fastcdr::Cdr& scdr,
        const UpdateCam& data)
{
    eprosima::fastcdr::Cdr::state current_state(scdr);
    scdr.begin_serialize_type(current_state,
            eprosima::fastcdr::CdrVersion::XCDRv2 == scdr.get_cdr_version() ?
            eprosima::fastcdr::EncodingAlgorithmFlag::DELIMIT_CDR2 :
            eprosima::fastcdr::EncodingAlgorithmFlag::PLAIN_CDR);

    scdr
        << eprosima::fastcdr::MemberId(0) << data.rtspUrl()
        << eprosima::fastcdr::MemberId(1) << data.valid()
        << eprosima::fastcdr::MemberId(2) << data.imgW()
        << eprosima::fastcdr::MemberId(3) << data.imgH()
        << eprosima::fastcdr::MemberId(4) << data.fpsNum()
        << eprosima::fastcdr::MemberId(5) << data.fpsDen()
        << eprosima::fastcdr::MemberId(6) << data.frmQueSz()
        << eprosima::fastcdr::MemberId(7) << data.detPyrLev()
        << eprosima::fastcdr::MemberId(8) << data.detMethodId()
        << eprosima::fastcdr::MemberId(9) << data.detNetworkId()
        << eprosima::fastcdr::MemberId(10) << data.detFrmsToSkip()
        << eprosima::fastcdr::MemberId(11) << data.mp4LocationAndPrefix()
        << eprosima::fastcdr::MemberId(12) << data.subscriber_initalize_time()
        << eprosima::fastcdr::MemberId(13) << data.publisher_send_time()
        << eprosima::fastcdr::MemberId(14) << data.subscriber_recieve_time()
;
    scdr.end_serialize_type(current_state);
}

template<>
eProsima_user_DllExport void deserialize(
        eprosima::fastcdr::Cdr& cdr,
        UpdateCam& data)
{
    cdr.deserialize_type(eprosima::fastcdr::CdrVersion::XCDRv2 == cdr.get_cdr_version() ?
            eprosima::fastcdr::EncodingAlgorithmFlag::DELIMIT_CDR2 :
            eprosima::fastcdr::EncodingAlgorithmFlag::PLAIN_CDR,
            [&data](eprosima::fastcdr::Cdr& dcdr, const eprosima::fastcdr::MemberId& mid) -> bool
            {
                bool ret_value = true;
                switch (mid.id)
                {
                                        case 0:
                                                dcdr >> data.rtspUrl();
                                            break;

                                        case 1:
                                                dcdr >> data.valid();
                                            break;

                                        case 2:
                                                dcdr >> data.imgW();
                                            break;

                                        case 3:
                                                dcdr >> data.imgH();
                                            break;

                                        case 4:
                                                dcdr >> data.fpsNum();
                                            break;

                                        case 5:
                                                dcdr >> data.fpsDen();
                                            break;

                                        case 6:
                                                dcdr >> data.frmQueSz();
                                            break;

                                        case 7:
                                                dcdr >> data.detPyrLev();
                                            break;

                                        case 8:
                                                dcdr >> data.detMethodId();
                                            break;

                                        case 9:
                                                dcdr >> data.detNetworkId();
                                            break;

                                        case 10:
                                                dcdr >> data.detFrmsToSkip();
                                            break;

                                        case 11:
                                                dcdr >> data.mp4LocationAndPrefix();
                                            break;

                                        case 12:
                                                dcdr >> data.subscriber_initalize_time();
                                            break;

                                        case 13:
                                                dcdr >> data.publisher_send_time();
                                            break;

                                        case 14:
                                                dcdr >> data.subscriber_recieve_time();
                                            break;

                    default:
                        ret_value = false;
                        break;
                }
                return ret_value;
            });
}

void serialize_key(
        eprosima::fastcdr::Cdr& scdr,
        const UpdateCam& data)
{
    static_cast<void>(scdr);
    static_cast<void>(data);
}



} // namespace fastcdr
} // namespace eprosima

#endif // _FAST_DDS_GENERATED_UPDATECAMCDRAUX_IPP_

