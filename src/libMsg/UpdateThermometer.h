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
 * @file UpdateThermometer.h
 * This header file contains the declaration of the described types in the IDL file.
 *
 * This file was generated by the tool fastddsgen.
 */

#ifndef _FAST_DDS_GENERATED_UPDATETHERMOMETER_H_
#define _FAST_DDS_GENERATED_UPDATETHERMOMETER_H_

#include <array>
#include <bitset>
#include <cstdint>
#include <map>
#include <string>
#include <vector>

#include <fastcdr/cdr/fixed_size_string.hpp>
#include <fastcdr/xcdr/external.hpp>
#include <fastcdr/xcdr/optional.hpp>



#if defined(_WIN32)
#if defined(EPROSIMA_USER_DLL_EXPORT)
#define eProsima_user_DllExport __declspec( dllexport )
#else
#define eProsima_user_DllExport
#endif  // EPROSIMA_USER_DLL_EXPORT
#else
#define eProsima_user_DllExport
#endif  // _WIN32

#if defined(_WIN32)
#if defined(EPROSIMA_USER_DLL_EXPORT)
#if defined(UPDATETHERMOMETER_SOURCE)
#define UPDATETHERMOMETER_DllAPI __declspec( dllexport )
#else
#define UPDATETHERMOMETER_DllAPI __declspec( dllimport )
#endif // UPDATETHERMOMETER_SOURCE
#else
#define UPDATETHERMOMETER_DllAPI
#endif  // EPROSIMA_USER_DLL_EXPORT
#else
#define UPDATETHERMOMETER_DllAPI
#endif // _WIN32

namespace eprosima {
namespace fastcdr {
class Cdr;
class CdrSizeCalculator;
} // namespace fastcdr
} // namespace eprosima





/*!
 * @brief This class represents the structure UpdateThermometer defined by the user in the IDL file.
 * @ingroup UpdateThermometer
 */
class UpdateThermometer
{
public:

    /*!
     * @brief Default constructor.
     */
    eProsima_user_DllExport UpdateThermometer();

    /*!
     * @brief Default destructor.
     */
    eProsima_user_DllExport ~UpdateThermometer();

    /*!
     * @brief Copy constructor.
     * @param x Reference to the object UpdateThermometer that will be copied.
     */
    eProsima_user_DllExport UpdateThermometer(
            const UpdateThermometer& x);

    /*!
     * @brief Move constructor.
     * @param x Reference to the object UpdateThermometer that will be copied.
     */
    eProsima_user_DllExport UpdateThermometer(
            UpdateThermometer&& x) noexcept;

    /*!
     * @brief Copy assignment.
     * @param x Reference to the object UpdateThermometer that will be copied.
     */
    eProsima_user_DllExport UpdateThermometer& operator =(
            const UpdateThermometer& x);

    /*!
     * @brief Move assignment.
     * @param x Reference to the object UpdateThermometer that will be copied.
     */
    eProsima_user_DllExport UpdateThermometer& operator =(
            UpdateThermometer&& x) noexcept;

    /*!
     * @brief Comparison operator.
     * @param x UpdateThermometer object to compare.
     */
    eProsima_user_DllExport bool operator ==(
            const UpdateThermometer& x) const;

    /*!
     * @brief Comparison operator.
     * @param x UpdateThermometer object to compare.
     */
    eProsima_user_DllExport bool operator !=(
            const UpdateThermometer& x) const;

    /*!
     * @brief This function sets a value in member subscriber_initalize_time
     * @param _subscriber_initalize_time New value for member subscriber_initalize_time
     */
    eProsima_user_DllExport void subscriber_initalize_time(
            uint64_t _subscriber_initalize_time);

    /*!
     * @brief This function returns the value of member subscriber_initalize_time
     * @return Value of member subscriber_initalize_time
     */
    eProsima_user_DllExport uint64_t subscriber_initalize_time() const;

    /*!
     * @brief This function returns a reference to member subscriber_initalize_time
     * @return Reference to member subscriber_initalize_time
     */
    eProsima_user_DllExport uint64_t& subscriber_initalize_time();


    /*!
     * @brief This function sets a value in member publisher_send_time
     * @param _publisher_send_time New value for member publisher_send_time
     */
    eProsima_user_DllExport void publisher_send_time(
            uint64_t _publisher_send_time);

    /*!
     * @brief This function returns the value of member publisher_send_time
     * @return Value of member publisher_send_time
     */
    eProsima_user_DllExport uint64_t publisher_send_time() const;

    /*!
     * @brief This function returns a reference to member publisher_send_time
     * @return Reference to member publisher_send_time
     */
    eProsima_user_DllExport uint64_t& publisher_send_time();


    /*!
     * @brief This function sets a value in member subscriber_recieve_time
     * @param _subscriber_recieve_time New value for member subscriber_recieve_time
     */
    eProsima_user_DllExport void subscriber_recieve_time(
            uint64_t _subscriber_recieve_time);

    /*!
     * @brief This function returns the value of member subscriber_recieve_time
     * @return Value of member subscriber_recieve_time
     */
    eProsima_user_DllExport uint64_t subscriber_recieve_time() const;

    /*!
     * @brief This function returns a reference to member subscriber_recieve_time
     * @return Reference to member subscriber_recieve_time
     */
    eProsima_user_DllExport uint64_t& subscriber_recieve_time();

private:

    uint64_t m_subscriber_initalize_time{0};
    uint64_t m_publisher_send_time{0};
    uint64_t m_subscriber_recieve_time{0};

};

#endif // _FAST_DDS_GENERATED_UPDATETHERMOMETER_H_



