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
 * @file HumidityTypeObject.cpp
 * This source file contains the definition of the described types in the IDL file.
 *
 * This file was generated by the tool gen.
 */

#ifdef _WIN32
// Remove linker warning LNK4221 on Visual Studio
namespace { char dummy; }
#endif

#include "Humidity.h"
#include "HumidityTypeObject.h"
#include <mutex>
#include <utility>
#include <sstream>
#include <fastrtps/rtps/common/SerializedPayload.h>
#include <fastrtps/utils/md5.h>
#include <fastrtps/types/TypeObjectFactory.h>
#include <fastrtps/types/TypeNamesGenerator.h>
#include <fastrtps/types/AnnotationParameterValue.h>
#include <fastcdr/FastBuffer.h>
#include <fastcdr/Cdr.h>

using namespace eprosima::fastrtps::rtps;

void registerHumidityTypes()
{
    static std::once_flag once_flag;
    std::call_once(once_flag, []()
            {
                TypeObjectFactory *factory = TypeObjectFactory::get_instance();
                factory->add_type_object("Humidity", GetHumidityIdentifier(true),
                GetHumidityObject(true));
                factory->add_type_object("Humidity", GetHumidityIdentifier(false),
                GetHumidityObject(false));

            });
}

const TypeIdentifier* GetHumidityIdentifier(bool complete)
{
    const TypeIdentifier * c_identifier = TypeObjectFactory::get_instance()->get_type_identifier("Humidity", complete);
    if (c_identifier != nullptr && (!complete || c_identifier->_d() == EK_COMPLETE))
    {
        return c_identifier;
    }

    GetHumidityObject(complete); // Generated inside
    return TypeObjectFactory::get_instance()->get_type_identifier("Humidity", complete);
}

const TypeObject* GetHumidityObject(bool complete)
{
    const TypeObject* c_type_object = TypeObjectFactory::get_instance()->get_type_object("Humidity", complete);
    if (c_type_object != nullptr)
    {
        return c_type_object;
    }
    else if (complete)
    {
        return GetCompleteHumidityObject();
    }
    //else
    return GetMinimalHumidityObject();
}

const TypeObject* GetMinimalHumidityObject()
{
    const TypeObject* c_type_object = TypeObjectFactory::get_instance()->get_type_object("Humidity", false);
    if (c_type_object != nullptr)
    {
        return c_type_object;
    }

    TypeObject *type_object = new TypeObject();
    type_object->_d(EK_MINIMAL);
    type_object->minimal()._d(TK_STRUCTURE);

    type_object->minimal().struct_type().struct_flags().IS_FINAL(false);
    type_object->minimal().struct_type().struct_flags().IS_APPENDABLE(false);
    type_object->minimal().struct_type().struct_flags().IS_MUTABLE(false);
    type_object->minimal().struct_type().struct_flags().IS_NESTED(false);
    type_object->minimal().struct_type().struct_flags().IS_AUTOID_HASH(false); // Unsupported

    MemberId memberId = 0;
    MinimalStructMember mst_index;
    mst_index.common().member_id(memberId++);
    mst_index.common().member_flags().TRY_CONSTRUCT1(false); // Unsupported
    mst_index.common().member_flags().TRY_CONSTRUCT2(false); // Unsupported
    mst_index.common().member_flags().IS_EXTERNAL(false); // Unsupported
    mst_index.common().member_flags().IS_OPTIONAL(false);
    mst_index.common().member_flags().IS_MUST_UNDERSTAND(false);
    mst_index.common().member_flags().IS_KEY(false);
    mst_index.common().member_flags().IS_DEFAULT(false); // Doesn't apply
    mst_index.common().member_type_id(*TypeObjectFactory::get_instance()->get_type_identifier("uint32_t", false));

    MD5 index_hash("index");
    for(int i = 0; i < 4; ++i)
    {
        mst_index.detail().name_hash()[i] = index_hash.digest[i];
    }
    type_object->minimal().struct_type().member_seq().emplace_back(mst_index);

    MinimalStructMember mst_humidity;
    mst_humidity.common().member_id(memberId++);
    mst_humidity.common().member_flags().TRY_CONSTRUCT1(false); // Unsupported
    mst_humidity.common().member_flags().TRY_CONSTRUCT2(false); // Unsupported
    mst_humidity.common().member_flags().IS_EXTERNAL(false); // Unsupported
    mst_humidity.common().member_flags().IS_OPTIONAL(false);
    mst_humidity.common().member_flags().IS_MUST_UNDERSTAND(false);
    mst_humidity.common().member_flags().IS_KEY(false);
    mst_humidity.common().member_flags().IS_DEFAULT(false); // Doesn't apply
    mst_humidity.common().member_type_id(*TypeObjectFactory::get_instance()->get_type_identifier("uint32_t", false));

    MD5 humidity_hash("humidity");
    for(int i = 0; i < 4; ++i)
    {
        mst_humidity.detail().name_hash()[i] = humidity_hash.digest[i];
    }
    type_object->minimal().struct_type().member_seq().emplace_back(mst_humidity);

    MinimalStructMember mst_subscriber_initalize_time;
    mst_subscriber_initalize_time.common().member_id(memberId++);
    mst_subscriber_initalize_time.common().member_flags().TRY_CONSTRUCT1(false); // Unsupported
    mst_subscriber_initalize_time.common().member_flags().TRY_CONSTRUCT2(false); // Unsupported
    mst_subscriber_initalize_time.common().member_flags().IS_EXTERNAL(false); // Unsupported
    mst_subscriber_initalize_time.common().member_flags().IS_OPTIONAL(false);
    mst_subscriber_initalize_time.common().member_flags().IS_MUST_UNDERSTAND(false);
    mst_subscriber_initalize_time.common().member_flags().IS_KEY(false);
    mst_subscriber_initalize_time.common().member_flags().IS_DEFAULT(false); // Doesn't apply
    mst_subscriber_initalize_time.common().member_type_id(*TypeObjectFactory::get_instance()->get_type_identifier("uint64_t", false));

    MD5 subscriber_initalize_time_hash("subscriber_initalize_time");
    for(int i = 0; i < 4; ++i)
    {
        mst_subscriber_initalize_time.detail().name_hash()[i] = subscriber_initalize_time_hash.digest[i];
    }
    type_object->minimal().struct_type().member_seq().emplace_back(mst_subscriber_initalize_time);

    MinimalStructMember mst_publisher_send_time;
    mst_publisher_send_time.common().member_id(memberId++);
    mst_publisher_send_time.common().member_flags().TRY_CONSTRUCT1(false); // Unsupported
    mst_publisher_send_time.common().member_flags().TRY_CONSTRUCT2(false); // Unsupported
    mst_publisher_send_time.common().member_flags().IS_EXTERNAL(false); // Unsupported
    mst_publisher_send_time.common().member_flags().IS_OPTIONAL(false);
    mst_publisher_send_time.common().member_flags().IS_MUST_UNDERSTAND(false);
    mst_publisher_send_time.common().member_flags().IS_KEY(false);
    mst_publisher_send_time.common().member_flags().IS_DEFAULT(false); // Doesn't apply
    mst_publisher_send_time.common().member_type_id(*TypeObjectFactory::get_instance()->get_type_identifier("uint64_t", false));

    MD5 publisher_send_time_hash("publisher_send_time");
    for(int i = 0; i < 4; ++i)
    {
        mst_publisher_send_time.detail().name_hash()[i] = publisher_send_time_hash.digest[i];
    }
    type_object->minimal().struct_type().member_seq().emplace_back(mst_publisher_send_time);

    MinimalStructMember mst_subscriber_recieve_time;
    mst_subscriber_recieve_time.common().member_id(memberId++);
    mst_subscriber_recieve_time.common().member_flags().TRY_CONSTRUCT1(false); // Unsupported
    mst_subscriber_recieve_time.common().member_flags().TRY_CONSTRUCT2(false); // Unsupported
    mst_subscriber_recieve_time.common().member_flags().IS_EXTERNAL(false); // Unsupported
    mst_subscriber_recieve_time.common().member_flags().IS_OPTIONAL(false);
    mst_subscriber_recieve_time.common().member_flags().IS_MUST_UNDERSTAND(false);
    mst_subscriber_recieve_time.common().member_flags().IS_KEY(false);
    mst_subscriber_recieve_time.common().member_flags().IS_DEFAULT(false); // Doesn't apply
    mst_subscriber_recieve_time.common().member_type_id(*TypeObjectFactory::get_instance()->get_type_identifier("uint64_t", false));

    MD5 subscriber_recieve_time_hash("subscriber_recieve_time");
    for(int i = 0; i < 4; ++i)
    {
        mst_subscriber_recieve_time.detail().name_hash()[i] = subscriber_recieve_time_hash.digest[i];
    }
    type_object->minimal().struct_type().member_seq().emplace_back(mst_subscriber_recieve_time);


    // Header
    // TODO Inheritance
    //type_object->minimal().struct_type().header().base_type()._d(EK_MINIMAL);
    //type_object->minimal().struct_type().header().base_type().equivalence_hash()[0..13];

    TypeIdentifier identifier;
    identifier._d(EK_MINIMAL);

    SerializedPayload_t payload(static_cast<uint32_t>(
        MinimalStructType::getCdrSerializedSize(type_object->minimal().struct_type()) + 4));
    eprosima::fastcdr::FastBuffer fastbuffer((char*) payload.data, payload.max_size);
    // Fixed endian (Page 221, EquivalenceHash definition of Extensible and Dynamic Topic Types for DDS document)
    eprosima::fastcdr::Cdr ser(
        fastbuffer, eprosima::fastcdr::Cdr::LITTLE_ENDIANNESS,
        eprosima::fastcdr::Cdr::DDS_CDR); // Object that serializes the data.
    payload.encapsulation = CDR_LE;

    type_object->serialize(ser);
    payload.length = (uint32_t)ser.getSerializedDataLength(); //Get the serialized length
    MD5 objectHash;
    objectHash.update((char*)payload.data, payload.length);
    objectHash.finalize();
    for(int i = 0; i < 14; ++i)
    {
        identifier.equivalence_hash()[i] = objectHash.digest[i];
    }

    TypeObjectFactory::get_instance()->add_type_object("Humidity", &identifier, type_object);
    delete type_object;
    return TypeObjectFactory::get_instance()->get_type_object("Humidity", false);
}

const TypeObject* GetCompleteHumidityObject()
{
    const TypeObject* c_type_object = TypeObjectFactory::get_instance()->get_type_object("Humidity", true);
    if (c_type_object != nullptr && c_type_object->_d() == EK_COMPLETE)
    {
        return c_type_object;
    }

    TypeObject *type_object = new TypeObject();
    type_object->_d(EK_COMPLETE);
    type_object->complete()._d(TK_STRUCTURE);

    type_object->complete().struct_type().struct_flags().IS_FINAL(false);
    type_object->complete().struct_type().struct_flags().IS_APPENDABLE(false);
    type_object->complete().struct_type().struct_flags().IS_MUTABLE(false);
    type_object->complete().struct_type().struct_flags().IS_NESTED(false);
    type_object->complete().struct_type().struct_flags().IS_AUTOID_HASH(false); // Unsupported

    MemberId memberId = 0;
    CompleteStructMember cst_index;
    cst_index.common().member_id(memberId++);
    cst_index.common().member_flags().TRY_CONSTRUCT1(false); // Unsupported
    cst_index.common().member_flags().TRY_CONSTRUCT2(false); // Unsupported
    cst_index.common().member_flags().IS_EXTERNAL(false); // Unsupported
    cst_index.common().member_flags().IS_OPTIONAL(false);
    cst_index.common().member_flags().IS_MUST_UNDERSTAND(false);
    cst_index.common().member_flags().IS_KEY(false);
    cst_index.common().member_flags().IS_DEFAULT(false); // Doesn't apply
    cst_index.common().member_type_id(*TypeObjectFactory::get_instance()->get_type_identifier("uint32_t", false));

    cst_index.detail().name("index");

    type_object->complete().struct_type().member_seq().emplace_back(cst_index);

    CompleteStructMember cst_humidity;
    cst_humidity.common().member_id(memberId++);
    cst_humidity.common().member_flags().TRY_CONSTRUCT1(false); // Unsupported
    cst_humidity.common().member_flags().TRY_CONSTRUCT2(false); // Unsupported
    cst_humidity.common().member_flags().IS_EXTERNAL(false); // Unsupported
    cst_humidity.common().member_flags().IS_OPTIONAL(false);
    cst_humidity.common().member_flags().IS_MUST_UNDERSTAND(false);
    cst_humidity.common().member_flags().IS_KEY(false);
    cst_humidity.common().member_flags().IS_DEFAULT(false); // Doesn't apply
    cst_humidity.common().member_type_id(*TypeObjectFactory::get_instance()->get_type_identifier("uint32_t", false));

    cst_humidity.detail().name("humidity");

    type_object->complete().struct_type().member_seq().emplace_back(cst_humidity);

    CompleteStructMember cst_subscriber_initalize_time;
    cst_subscriber_initalize_time.common().member_id(memberId++);
    cst_subscriber_initalize_time.common().member_flags().TRY_CONSTRUCT1(false); // Unsupported
    cst_subscriber_initalize_time.common().member_flags().TRY_CONSTRUCT2(false); // Unsupported
    cst_subscriber_initalize_time.common().member_flags().IS_EXTERNAL(false); // Unsupported
    cst_subscriber_initalize_time.common().member_flags().IS_OPTIONAL(false);
    cst_subscriber_initalize_time.common().member_flags().IS_MUST_UNDERSTAND(false);
    cst_subscriber_initalize_time.common().member_flags().IS_KEY(false);
    cst_subscriber_initalize_time.common().member_flags().IS_DEFAULT(false); // Doesn't apply
    cst_subscriber_initalize_time.common().member_type_id(*TypeObjectFactory::get_instance()->get_type_identifier("uint64_t", false));

    cst_subscriber_initalize_time.detail().name("subscriber_initalize_time");

    type_object->complete().struct_type().member_seq().emplace_back(cst_subscriber_initalize_time);

    CompleteStructMember cst_publisher_send_time;
    cst_publisher_send_time.common().member_id(memberId++);
    cst_publisher_send_time.common().member_flags().TRY_CONSTRUCT1(false); // Unsupported
    cst_publisher_send_time.common().member_flags().TRY_CONSTRUCT2(false); // Unsupported
    cst_publisher_send_time.common().member_flags().IS_EXTERNAL(false); // Unsupported
    cst_publisher_send_time.common().member_flags().IS_OPTIONAL(false);
    cst_publisher_send_time.common().member_flags().IS_MUST_UNDERSTAND(false);
    cst_publisher_send_time.common().member_flags().IS_KEY(false);
    cst_publisher_send_time.common().member_flags().IS_DEFAULT(false); // Doesn't apply
    cst_publisher_send_time.common().member_type_id(*TypeObjectFactory::get_instance()->get_type_identifier("uint64_t", false));

    cst_publisher_send_time.detail().name("publisher_send_time");

    type_object->complete().struct_type().member_seq().emplace_back(cst_publisher_send_time);

    CompleteStructMember cst_subscriber_recieve_time;
    cst_subscriber_recieve_time.common().member_id(memberId++);
    cst_subscriber_recieve_time.common().member_flags().TRY_CONSTRUCT1(false); // Unsupported
    cst_subscriber_recieve_time.common().member_flags().TRY_CONSTRUCT2(false); // Unsupported
    cst_subscriber_recieve_time.common().member_flags().IS_EXTERNAL(false); // Unsupported
    cst_subscriber_recieve_time.common().member_flags().IS_OPTIONAL(false);
    cst_subscriber_recieve_time.common().member_flags().IS_MUST_UNDERSTAND(false);
    cst_subscriber_recieve_time.common().member_flags().IS_KEY(false);
    cst_subscriber_recieve_time.common().member_flags().IS_DEFAULT(false); // Doesn't apply
    cst_subscriber_recieve_time.common().member_type_id(*TypeObjectFactory::get_instance()->get_type_identifier("uint64_t", false));

    cst_subscriber_recieve_time.detail().name("subscriber_recieve_time");

    type_object->complete().struct_type().member_seq().emplace_back(cst_subscriber_recieve_time);


    // Header
    type_object->complete().struct_type().header().detail().type_name("Humidity");
    // TODO inheritance


    TypeIdentifier identifier;
    identifier._d(EK_COMPLETE);

    SerializedPayload_t payload(static_cast<uint32_t>(
        CompleteStructType::getCdrSerializedSize(type_object->complete().struct_type()) + 4));
    eprosima::fastcdr::FastBuffer fastbuffer((char*) payload.data, payload.max_size);
    // Fixed endian (Page 221, EquivalenceHash definition of Extensible and Dynamic Topic Types for DDS document)
    eprosima::fastcdr::Cdr ser(
        fastbuffer, eprosima::fastcdr::Cdr::LITTLE_ENDIANNESS,
        eprosima::fastcdr::Cdr::DDS_CDR); // Object that serializes the data.
    payload.encapsulation = CDR_LE;

    type_object->serialize(ser);
    payload.length = (uint32_t)ser.getSerializedDataLength(); //Get the serialized length
    MD5 objectHash;
    objectHash.update((char*)payload.data, payload.length);
    objectHash.finalize();
    for(int i = 0; i < 14; ++i)
    {
        identifier.equivalence_hash()[i] = objectHash.digest[i];
    }

    TypeObjectFactory::get_instance()->add_type_object("Humidity", &identifier, type_object);
    delete type_object;
    return TypeObjectFactory::get_instance()->get_type_object("Humidity", true);
}
