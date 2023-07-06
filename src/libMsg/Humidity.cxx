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
 * @file Humidity.cpp
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

#include "Humidity.h"
#include <fastcdr/Cdr.h>

#include <fastcdr/exceptions/BadParamException.h>
using namespace eprosima::fastcdr::exception;

#include <utility>

Humidity::Humidity()
{
    // m_humidity com.eprosima.idl.parser.typecode.PrimitiveTypeCode@42607a4f
    m_humidity = 0;
    // m_timestamp com.eprosima.idl.parser.typecode.StringTypeCode@64485a47
    m_timestamp ="";

}

Humidity::~Humidity()
{


}

Humidity::Humidity(
        const Humidity& x)
{
    m_humidity = x.m_humidity;
    m_timestamp = x.m_timestamp;
}

Humidity::Humidity(
        Humidity&& x) noexcept 
{
    m_humidity = x.m_humidity;
    m_timestamp = std::move(x.m_timestamp);
}

Humidity& Humidity::operator =(
        const Humidity& x)
{

    m_humidity = x.m_humidity;
    m_timestamp = x.m_timestamp;

    return *this;
}

Humidity& Humidity::operator =(
        Humidity&& x) noexcept
{

    m_humidity = x.m_humidity;
    m_timestamp = std::move(x.m_timestamp);

    return *this;
}

bool Humidity::operator ==(
        const Humidity& x) const
{

    return (m_humidity == x.m_humidity && m_timestamp == x.m_timestamp);
}

bool Humidity::operator !=(
        const Humidity& x) const
{
    return !(*this == x);
}

size_t Humidity::getMaxCdrSerializedSize(
        size_t current_alignment)
{
    size_t initial_alignment = current_alignment;


    current_alignment += 4 + eprosima::fastcdr::Cdr::alignment(current_alignment, 4);


    current_alignment += 4 + eprosima::fastcdr::Cdr::alignment(current_alignment, 4) + 255 + 1;


    return current_alignment - initial_alignment;
}

size_t Humidity::getCdrSerializedSize(
        const Humidity& data,
        size_t current_alignment)
{
    (void)data;
    size_t initial_alignment = current_alignment;


    current_alignment += 4 + eprosima::fastcdr::Cdr::alignment(current_alignment, 4);


    current_alignment += 4 + eprosima::fastcdr::Cdr::alignment(current_alignment, 4) + data.timestamp().size() + 1;


    return current_alignment - initial_alignment;
}

void Humidity::serialize(
        eprosima::fastcdr::Cdr& scdr) const
{

    scdr << m_humidity;
    scdr << m_timestamp.c_str();

}

void Humidity::deserialize(
        eprosima::fastcdr::Cdr& dcdr)
{

    dcdr >> m_humidity;
    dcdr >> m_timestamp;
}

/*!
 * @brief This function sets a value in member humidity
 * @param _humidity New value for member humidity
 */
void Humidity::humidity(
        uint32_t _humidity)
{
    m_humidity = _humidity;
}

/*!
 * @brief This function returns the value of member humidity
 * @return Value of member humidity
 */
uint32_t Humidity::humidity() const
{
    return m_humidity;
}

/*!
 * @brief This function returns a reference to member humidity
 * @return Reference to member humidity
 */
uint32_t& Humidity::humidity()
{
    return m_humidity;
}

/*!
 * @brief This function copies the value in member timestamp
 * @param _timestamp New value to be copied in member timestamp
 */
void Humidity::timestamp(
        const std::string& _timestamp)
{
    m_timestamp = _timestamp;
}

/*!
 * @brief This function moves the value in member timestamp
 * @param _timestamp New value to be moved in member timestamp
 */
void Humidity::timestamp(
        std::string&& _timestamp)
{
    m_timestamp = std::move(_timestamp);
}

/*!
 * @brief This function returns a constant reference to member timestamp
 * @return Constant reference to member timestamp
 */
const std::string& Humidity::timestamp() const
{
    return m_timestamp;
}

/*!
 * @brief This function returns a reference to member timestamp
 * @return Reference to member timestamp
 */
std::string& Humidity::timestamp()
{
    return m_timestamp;
}

size_t Humidity::getKeyMaxCdrSerializedSize(
        size_t current_alignment)
{
    size_t current_align = current_alignment;





    return current_align;
}

bool Humidity::isKeyDefined()
{
    return false;
}

void Humidity::serializeKey(
        eprosima::fastcdr::Cdr& scdr) const
{
    (void) scdr;
      
}