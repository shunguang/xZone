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
 * @file UpdateThermometer.cpp
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

#include "UpdateThermometer.h"
#include <fastcdr/Cdr.h>

#include <fastcdr/exceptions/BadParamException.h>
using namespace eprosima::fastcdr::exception;

#include <utility>

#define UpdateThermometer_max_cdr_typesize 28ULL;
#define UpdateThermometer_max_key_cdr_typesize 0ULL;

UpdateThermometer::UpdateThermometer()
{
    // unsigned long long m_t1
    m_t1 = 0;
    // unsigned long long m_t2
    m_t2 = 0;
    // unsigned long long m_t3
    m_t3 = 0;
    // long m_frequency
    m_frequency = 0;

}

UpdateThermometer::~UpdateThermometer()
{




}

UpdateThermometer::UpdateThermometer(
        const UpdateThermometer& x)
{
    m_t1 = x.m_t1;
    m_t2 = x.m_t2;
    m_t3 = x.m_t3;
    m_frequency = x.m_frequency;
}

UpdateThermometer::UpdateThermometer(
        UpdateThermometer&& x) noexcept 
{
    m_t1 = x.m_t1;
    m_t2 = x.m_t2;
    m_t3 = x.m_t3;
    m_frequency = x.m_frequency;
}

UpdateThermometer& UpdateThermometer::operator =(
        const UpdateThermometer& x)
{

    m_t1 = x.m_t1;
    m_t2 = x.m_t2;
    m_t3 = x.m_t3;
    m_frequency = x.m_frequency;

    return *this;
}

UpdateThermometer& UpdateThermometer::operator =(
        UpdateThermometer&& x) noexcept
{

    m_t1 = x.m_t1;
    m_t2 = x.m_t2;
    m_t3 = x.m_t3;
    m_frequency = x.m_frequency;

    return *this;
}

bool UpdateThermometer::operator ==(
        const UpdateThermometer& x) const
{

    return (m_t1 == x.m_t1 && m_t2 == x.m_t2 && m_t3 == x.m_t3 && m_frequency == x.m_frequency);
}

bool UpdateThermometer::operator !=(
        const UpdateThermometer& x) const
{
    return !(*this == x);
}

size_t UpdateThermometer::getMaxCdrSerializedSize(
        size_t current_alignment)
{
    static_cast<void>(current_alignment);
    return UpdateThermometer_max_cdr_typesize;
}

size_t UpdateThermometer::getCdrSerializedSize(
        const UpdateThermometer& data,
        size_t current_alignment)
{
    (void)data;
    size_t initial_alignment = current_alignment;


    current_alignment += 8 + eprosima::fastcdr::Cdr::alignment(current_alignment, 8);


    current_alignment += 8 + eprosima::fastcdr::Cdr::alignment(current_alignment, 8);


    current_alignment += 8 + eprosima::fastcdr::Cdr::alignment(current_alignment, 8);


    current_alignment += 4 + eprosima::fastcdr::Cdr::alignment(current_alignment, 4);



    return current_alignment - initial_alignment;
}

void UpdateThermometer::serialize(
        eprosima::fastcdr::Cdr& scdr) const
{

    scdr << m_t1;
    scdr << m_t2;
    scdr << m_t3;
    scdr << m_frequency;

}

void UpdateThermometer::deserialize(
        eprosima::fastcdr::Cdr& dcdr)
{

    dcdr >> m_t1;
    dcdr >> m_t2;
    dcdr >> m_t3;
    dcdr >> m_frequency;
}

/*!
 * @brief This function sets a value in member t1
 * @param _t1 New value for member t1
 */
void UpdateThermometer::t1(
        uint64_t _t1)
{
    m_t1 = _t1;
}

/*!
 * @brief This function returns the value of member t1
 * @return Value of member t1
 */
uint64_t UpdateThermometer::t1() const
{
    return m_t1;
}

/*!
 * @brief This function returns a reference to member t1
 * @return Reference to member t1
 */
uint64_t& UpdateThermometer::t1()
{
    return m_t1;
}

/*!
 * @brief This function sets a value in member t2
 * @param _t2 New value for member t2
 */
void UpdateThermometer::t2(
        uint64_t _t2)
{
    m_t2 = _t2;
}

/*!
 * @brief This function returns the value of member t2
 * @return Value of member t2
 */
uint64_t UpdateThermometer::t2() const
{
    return m_t2;
}

/*!
 * @brief This function returns a reference to member t2
 * @return Reference to member t2
 */
uint64_t& UpdateThermometer::t2()
{
    return m_t2;
}

/*!
 * @brief This function sets a value in member t3
 * @param _t3 New value for member t3
 */
void UpdateThermometer::t3(
        uint64_t _t3)
{
    m_t3 = _t3;
}

/*!
 * @brief This function returns the value of member t3
 * @return Value of member t3
 */
uint64_t UpdateThermometer::t3() const
{
    return m_t3;
}

/*!
 * @brief This function returns a reference to member t3
 * @return Reference to member t3
 */
uint64_t& UpdateThermometer::t3()
{
    return m_t3;
}

/*!
 * @brief This function sets a value in member frequency
 * @param _frequency New value for member frequency
 */
void UpdateThermometer::frequency(
        int32_t _frequency)
{
    m_frequency = _frequency;
}

/*!
 * @brief This function returns the value of member frequency
 * @return Value of member frequency
 */
int32_t UpdateThermometer::frequency() const
{
    return m_frequency;
}

/*!
 * @brief This function returns a reference to member frequency
 * @return Reference to member frequency
 */
int32_t& UpdateThermometer::frequency()
{
    return m_frequency;
}



size_t UpdateThermometer::getKeyMaxCdrSerializedSize(
        size_t current_alignment)
{
    static_cast<void>(current_alignment);
    return UpdateThermometer_max_key_cdr_typesize;
}

bool UpdateThermometer::isKeyDefined()
{
    return false;
}

void UpdateThermometer::serializeKey(
        eprosima::fastcdr::Cdr& scdr) const
{
    (void) scdr;
}

