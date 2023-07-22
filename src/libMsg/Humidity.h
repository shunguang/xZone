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
 * @file Humidity.h
 * This header file contains the declaration of the described types in the IDL file.
 *
 * This file was generated by the tool gen.
 */

#ifndef _FAST_DDS_GENERATED_HUMIDITY_H_
#define _FAST_DDS_GENERATED_HUMIDITY_H_


#include <fastrtps/utils/fixed_size_string.hpp>

#include <stdint.h>
#include <array>
#include <string>
#include <vector>
#include <map>
#include <bitset>

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
#if defined(HUMIDITY_SOURCE)
#define HUMIDITY_DllAPI __declspec( dllexport )
#else
#define HUMIDITY_DllAPI __declspec( dllimport )
#endif // HUMIDITY_SOURCE
#else
#define HUMIDITY_DllAPI
#endif  // EPROSIMA_USER_DLL_EXPORT
#else
#define HUMIDITY_DllAPI
#endif // _WIN32

namespace eprosima {
namespace fastcdr {
class Cdr;
} // namespace fastcdr
} // namespace eprosima


/*!
 * @brief This class represents the structure Humidity defined by the user in the IDL file.
 * @ingroup Humidity
 */
class Humidity
{
public:

    /*!
     * @brief Default constructor.
     */
    eProsima_user_DllExport Humidity();

    /*!
     * @brief Default destructor.
     */
    eProsima_user_DllExport ~Humidity();

    /*!
     * @brief Copy constructor.
     * @param x Reference to the object Humidity that will be copied.
     */
    eProsima_user_DllExport Humidity(
            const Humidity& x);

    /*!
     * @brief Move constructor.
     * @param x Reference to the object Humidity that will be copied.
     */
    eProsima_user_DllExport Humidity(
            Humidity&& x) noexcept;

    /*!
     * @brief Copy assignment.
     * @param x Reference to the object Humidity that will be copied.
     */
    eProsima_user_DllExport Humidity& operator =(
            const Humidity& x);

    /*!
     * @brief Move assignment.
     * @param x Reference to the object Humidity that will be copied.
     */
    eProsima_user_DllExport Humidity& operator =(
            Humidity&& x) noexcept;

    /*!
     * @brief Comparison operator.
     * @param x Humidity object to compare.
     */
    eProsima_user_DllExport bool operator ==(
            const Humidity& x) const;

    /*!
     * @brief Comparison operator.
     * @param x Humidity object to compare.
     */
    eProsima_user_DllExport bool operator !=(
            const Humidity& x) const;

    /*!
     * @brief This function sets a value in member humidity
     * @param _humidity New value for member humidity
     */
    eProsima_user_DllExport void humidity(
            uint32_t _humidity);

    /*!
     * @brief This function returns the value of member humidity
     * @return Value of member humidity
     */
    eProsima_user_DllExport uint32_t humidity() const;

    /*!
     * @brief This function returns a reference to member humidity
     * @return Reference to member humidity
     */
    eProsima_user_DllExport uint32_t& humidity();

    /*!
     * @brief This function copies the value in member timestamp
     * @param _timestamp New value to be copied in member timestamp
     */
    eProsima_user_DllExport void timestamp(
            const std::string& _timestamp);

    /*!
     * @brief This function moves the value in member timestamp
     * @param _timestamp New value to be moved in member timestamp
     */
    eProsima_user_DllExport void timestamp(
            std::string&& _timestamp);

    /*!
     * @brief This function returns a constant reference to member timestamp
     * @return Constant reference to member timestamp
     */
    eProsima_user_DllExport const std::string& timestamp() const;

    /*!
     * @brief This function returns a reference to member timestamp
     * @return Reference to member timestamp
     */
    eProsima_user_DllExport std::string& timestamp();
    /*!
     * @brief This function sets a value in member t1
     * @param _t1 New value for member t1
     */
    eProsima_user_DllExport void t1(
            uint64_t _t1);

    /*!
     * @brief This function returns the value of member t1
     * @return Value of member t1
     */
    eProsima_user_DllExport uint64_t t1() const;

    /*!
     * @brief This function returns a reference to member t1
     * @return Reference to member t1
     */
    eProsima_user_DllExport uint64_t& t1();

    /*!
     * @brief This function sets a value in member t2
     * @param _t2 New value for member t2
     */
    eProsima_user_DllExport void t2(
            uint64_t _t2);

    /*!
     * @brief This function returns the value of member t2
     * @return Value of member t2
     */
    eProsima_user_DllExport uint64_t t2() const;

    /*!
     * @brief This function returns a reference to member t2
     * @return Reference to member t2
     */
    eProsima_user_DllExport uint64_t& t2();

    /*!
     * @brief This function sets a value in member t3
     * @param _t3 New value for member t3
     */
    eProsima_user_DllExport void t3(
            uint64_t _t3);

    /*!
     * @brief This function returns the value of member t3
     * @return Value of member t3
     */
    eProsima_user_DllExport uint64_t t3() const;

    /*!
     * @brief This function returns a reference to member t3
     * @return Reference to member t3
     */
    eProsima_user_DllExport uint64_t& t3();

    /*!
     * @brief This function sets a value in member frequency
     * @param _frequency New value for member frequency
     */
    eProsima_user_DllExport void frequency(
            int32_t _frequency);

    /*!
     * @brief This function returns the value of member frequency
     * @return Value of member frequency
     */
    eProsima_user_DllExport int32_t frequency() const;

    /*!
     * @brief This function returns a reference to member frequency
     * @return Reference to member frequency
     */
    eProsima_user_DllExport int32_t& frequency();


    /*!
    * @brief This function returns the maximum serialized size of an object
    * depending on the buffer alignment.
    * @param current_alignment Buffer alignment.
    * @return Maximum serialized size.
    */
    eProsima_user_DllExport static size_t getMaxCdrSerializedSize(
            size_t current_alignment = 0);

    /*!
     * @brief This function returns the serialized size of a data depending on the buffer alignment.
     * @param data Data which is calculated its serialized size.
     * @param current_alignment Buffer alignment.
     * @return Serialized size.
     */
    eProsima_user_DllExport static size_t getCdrSerializedSize(
            const Humidity& data,
            size_t current_alignment = 0);


    /*!
     * @brief This function serializes an object using CDR serialization.
     * @param cdr CDR serialization object.
     */
    eProsima_user_DllExport void serialize(
            eprosima::fastcdr::Cdr& cdr) const;

    /*!
     * @brief This function deserializes an object using CDR serialization.
     * @param cdr CDR serialization object.
     */
    eProsima_user_DllExport void deserialize(
            eprosima::fastcdr::Cdr& cdr);



    /*!
     * @brief This function returns the maximum serialized size of the Key of an object
     * depending on the buffer alignment.
     * @param current_alignment Buffer alignment.
     * @return Maximum serialized size.
     */
    eProsima_user_DllExport static size_t getKeyMaxCdrSerializedSize(
            size_t current_alignment = 0);

    /*!
     * @brief This function tells you if the Key has been defined for this type
     */
    eProsima_user_DllExport static bool isKeyDefined();

    /*!
     * @brief This function serializes the key members of an object using CDR serialization.
     * @param cdr CDR serialization object.
     */
    eProsima_user_DllExport void serializeKey(
            eprosima::fastcdr::Cdr& cdr) const;

private:

    uint32_t m_humidity;
    std::string m_timestamp;
    uint64_t m_t1;
    uint64_t m_t2;
    uint64_t m_t3;
    int32_t m_frequency;

};

#endif // _FAST_DDS_GENERATED_HUMIDITY_H_

