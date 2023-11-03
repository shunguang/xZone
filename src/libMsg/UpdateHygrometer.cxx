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
 * @file UpdateHygrometer.cpp
 * This source file contains the definition of the described types in the IDL file.
 *
 * This file was generated by the tool gen.
 */

#ifdef _WIN32
// Remove linker warning LNK4221 on Visual Studio
namespace {
char dummy;
}  // namespace
#endif  // _WIN32

#include "UpdateHygrometer.h"
#include <fastcdr/Cdr.h>

#include <fastcdr/exceptions/BadParamException.h>
using namespace eprosima::fastcdr::exception;

#include <utility>

#define UpdateHygrometer_max_cdr_typesize 24ULL;
#define UpdateHygrometer_max_key_cdr_typesize 0ULL;

UpdateHygrometer::UpdateHygrometer()
{
    // unsigned long long m_subscriber_initalize_time
    m_subscriber_initalize_time = 0;
    // unsigned long long m_publisher_send_time
    m_publisher_send_time = 0;
    // unsigned long long m_subscriber_recieve_time
    m_subscriber_recieve_time = 0;

}

UpdateHygrometer::~UpdateHygrometer()
{



}

UpdateHygrometer::UpdateHygrometer(
        const UpdateHygrometer& x)
{
    m_subscriber_initalize_time = x.m_subscriber_initalize_time;
    m_publisher_send_time = x.m_publisher_send_time;
    m_subscriber_recieve_time = x.m_subscriber_recieve_time;
}

UpdateHygrometer::UpdateHygrometer(
        UpdateHygrometer&& x) noexcept 
{
    m_subscriber_initalize_time = x.m_subscriber_initalize_time;
    m_publisher_send_time = x.m_publisher_send_time;
    m_subscriber_recieve_time = x.m_subscriber_recieve_time;
}

UpdateHygrometer& UpdateHygrometer::operator =(
        const UpdateHygrometer& x)
{

    m_subscriber_initalize_time = x.m_subscriber_initalize_time;
    m_publisher_send_time = x.m_publisher_send_time;
    m_subscriber_recieve_time = x.m_subscriber_recieve_time;

    return *this;
}

UpdateHygrometer& UpdateHygrometer::operator =(
        UpdateHygrometer&& x) noexcept
{

    m_subscriber_initalize_time = x.m_subscriber_initalize_time;
    m_publisher_send_time = x.m_publisher_send_time;
    m_subscriber_recieve_time = x.m_subscriber_recieve_time;

    return *this;
}

bool UpdateHygrometer::operator ==(
        const UpdateHygrometer& x) const
{

    return (m_subscriber_initalize_time == x.m_subscriber_initalize_time && m_publisher_send_time == x.m_publisher_send_time && m_subscriber_recieve_time == x.m_subscriber_recieve_time);
}

bool UpdateHygrometer::operator !=(
        const UpdateHygrometer& x) const
{
    return !(*this == x);
}

size_t UpdateHygrometer::getMaxCdrSerializedSize(
        size_t current_alignment)
{
    static_cast<void>(current_alignment);
    return UpdateHygrometer_max_cdr_typesize;
}

size_t UpdateHygrometer::getCdrSerializedSize(
        const UpdateHygrometer& data,
        size_t current_alignment)
{
    (void)data;
    size_t initial_alignment = current_alignment;


    current_alignment += 8 + eprosima::fastcdr::Cdr::alignment(current_alignment, 8);


    current_alignment += 8 + eprosima::fastcdr::Cdr::alignment(current_alignment, 8);


    current_alignment += 8 + eprosima::fastcdr::Cdr::alignment(current_alignment, 8);



    return current_alignment - initial_alignment;
}

void UpdateHygrometer::serialize(
        eprosima::fastcdr::Cdr& scdr) const
{

    scdr << m_subscriber_initalize_time;
    scdr << m_publisher_send_time;
    scdr << m_subscriber_recieve_time;

}

void UpdateHygrometer::deserialize(
        eprosima::fastcdr::Cdr& dcdr)
{

    dcdr >> m_subscriber_initalize_time;
    dcdr >> m_publisher_send_time;
    dcdr >> m_subscriber_recieve_time;
}

/*!
 * @brief This function sets a value in member subscriber_initalize_time
 * @param _subscriber_initalize_time New value for member subscriber_initalize_time
 */
void UpdateHygrometer::subscriber_initalize_time(
        uint64_t _subscriber_initalize_time)
{
    m_subscriber_initalize_time = _subscriber_initalize_time;
}

/*!
 * @brief This function returns the value of member subscriber_initalize_time
 * @return Value of member subscriber_initalize_time
 */
uint64_t UpdateHygrometer::subscriber_initalize_time() const
{
    return m_subscriber_initalize_time;
}

/*!
 * @brief This function returns a reference to member subscriber_initalize_time
 * @return Reference to member subscriber_initalize_time
 */
uint64_t& UpdateHygrometer::subscriber_initalize_time()
{
    return m_subscriber_initalize_time;
}

/*!
 * @brief This function sets a value in member publisher_send_time
 * @param _publisher_send_time New value for member publisher_send_time
 */
void UpdateHygrometer::publisher_send_time(
        uint64_t _publisher_send_time)
{
    m_publisher_send_time = _publisher_send_time;
}

/*!
 * @brief This function returns the value of member publisher_send_time
 * @return Value of member publisher_send_time
 */
uint64_t UpdateHygrometer::publisher_send_time() const
{
    return m_publisher_send_time;
}

/*!
 * @brief This function returns a reference to member publisher_send_time
 * @return Reference to member publisher_send_time
 */
uint64_t& UpdateHygrometer::publisher_send_time()
{
    return m_publisher_send_time;
}

/*!
 * @brief This function sets a value in member subscriber_recieve_time
 * @param _subscriber_recieve_time New value for member subscriber_recieve_time
 */
void UpdateHygrometer::subscriber_recieve_time(
        uint64_t _subscriber_recieve_time)
{
    m_subscriber_recieve_time = _subscriber_recieve_time;
}

/*!
 * @brief This function returns the value of member subscriber_recieve_time
 * @return Value of member subscriber_recieve_time
 */
uint64_t UpdateHygrometer::subscriber_recieve_time() const
{
    return m_subscriber_recieve_time;
}

/*!
 * @brief This function returns a reference to member subscriber_recieve_time
 * @return Reference to member subscriber_recieve_time
 */
uint64_t& UpdateHygrometer::subscriber_recieve_time()
{
    return m_subscriber_recieve_time;
}



size_t UpdateHygrometer::getKeyMaxCdrSerializedSize(
        size_t current_alignment)
{
    static_cast<void>(current_alignment);
    return UpdateHygrometer_max_key_cdr_typesize;
}

bool UpdateHygrometer::isKeyDefined()
{
    return false;
}

void UpdateHygrometer::serializeKey(
        eprosima::fastcdr::Cdr& scdr) const
{
    (void) scdr;
}

