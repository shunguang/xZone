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
 * @file ImageTypeObject.cpp
 * This source file contains the definition of the described types in the IDL file.
 *
 * This file was generated by the tool fastddsgen.
 */

#ifdef _WIN32
// Remove linker warning LNK4221 on Visual Studio
namespace { char dummy; }
#endif

#include "Image.h"
#include "ImageTypeObject.h"
#include <mutex>
#include <utility>
#include <sstream>
#include <fastdds/rtps/common/CdrSerialization.hpp>
#include <fastrtps/rtps/common/SerializedPayload.h>
#include <fastrtps/utils/md5.h>
#include <fastrtps/types/TypeObjectFactory.h>
#include <fastrtps/types/TypeNamesGenerator.h>
#include <fastrtps/types/AnnotationParameterValue.h>

using namespace eprosima::fastrtps::rtps;

void registerImageTypes()
{
    static std::once_flag once_flag;
    std::call_once(once_flag, []()
            {
                TypeObjectFactory *factory = TypeObjectFactory::get_instance();
                factory->add_type_object("Image", GetImageIdentifier(true),
                GetImageObject(true));
                factory->add_type_object("Image", GetImageIdentifier(false),
                GetImageObject(false));

            });
}



const TypeIdentifier* GetImageIdentifier(bool complete)
{
    const TypeIdentifier * c_identifier = TypeObjectFactory::get_instance()->get_type_identifier("Image", complete);
    if (c_identifier != nullptr && (!complete || c_identifier->_d() == EK_COMPLETE))
    {
        return c_identifier;
    }

    GetImageObject(complete); // Generated inside
    return TypeObjectFactory::get_instance()->get_type_identifier("Image", complete);
}

const TypeObject* GetImageObject(bool complete)
{
    const TypeObject* c_type_object = TypeObjectFactory::get_instance()->get_type_object("Image", complete);
    if (c_type_object != nullptr)
    {
        return c_type_object;
    }
    else if (complete)
    {
        return GetCompleteImageObject();
    }
    //else
    return GetMinimalImageObject();
}

const TypeObject* GetMinimalImageObject()
{
    const TypeObject* c_type_object = TypeObjectFactory::get_instance()->get_type_object("Image", false);
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
    MinimalStructMember mst_image;
    mst_image.common().member_id(memberId++);
    mst_image.common().member_flags().TRY_CONSTRUCT1(false); // Unsupported
    mst_image.common().member_flags().TRY_CONSTRUCT2(false); // Unsupported
    mst_image.common().member_flags().IS_EXTERNAL(false); // Unsupported
    mst_image.common().member_flags().IS_OPTIONAL(false);
    mst_image.common().member_flags().IS_MUST_UNDERSTAND(false);
    mst_image.common().member_flags().IS_KEY(false);
    mst_image.common().member_flags().IS_DEFAULT(false); // Doesn't apply
    mst_image.common().member_type_id(*TypeObjectFactory::get_instance()->get_sequence_identifier("uint8_t", 100, false));

    MD5 image_hash("image");
    for(int i = 0; i < 4; ++i)
    {
        mst_image.detail().name_hash()[i] = image_hash.digest[i];
    }
    type_object->minimal().struct_type().member_seq().emplace_back(mst_image);

    MinimalStructMember mst_frame_number;
    mst_frame_number.common().member_id(memberId++);
    mst_frame_number.common().member_flags().TRY_CONSTRUCT1(false); // Unsupported
    mst_frame_number.common().member_flags().TRY_CONSTRUCT2(false); // Unsupported
    mst_frame_number.common().member_flags().IS_EXTERNAL(false); // Unsupported
    mst_frame_number.common().member_flags().IS_OPTIONAL(false);
    mst_frame_number.common().member_flags().IS_MUST_UNDERSTAND(false);
    mst_frame_number.common().member_flags().IS_KEY(false);
    mst_frame_number.common().member_flags().IS_DEFAULT(false); // Doesn't apply
    mst_frame_number.common().member_type_id(*TypeObjectFactory::get_instance()->get_type_identifier("uint32_t", false));


    MD5 frame_number_hash("frame_number");
    for(int i = 0; i < 4; ++i)
    {
        mst_frame_number.detail().name_hash()[i] = frame_number_hash.digest[i];
    }
    type_object->minimal().struct_type().member_seq().emplace_back(mst_frame_number);

    MinimalStructMember mst_frequency;
    mst_frequency.common().member_id(memberId++);
    mst_frequency.common().member_flags().TRY_CONSTRUCT1(false); // Unsupported
    mst_frequency.common().member_flags().TRY_CONSTRUCT2(false); // Unsupported
    mst_frequency.common().member_flags().IS_EXTERNAL(false); // Unsupported
    mst_frequency.common().member_flags().IS_OPTIONAL(false);
    mst_frequency.common().member_flags().IS_MUST_UNDERSTAND(false);
    mst_frequency.common().member_flags().IS_KEY(false);
    mst_frequency.common().member_flags().IS_DEFAULT(false); // Doesn't apply
    mst_frequency.common().member_type_id(*TypeObjectFactory::get_instance()->get_type_identifier("uint32_t", false));


    MD5 frequency_hash("frequency");
    for(int i = 0; i < 4; ++i)
    {
        mst_frequency.detail().name_hash()[i] = frequency_hash.digest[i];
    }
    type_object->minimal().struct_type().member_seq().emplace_back(mst_frequency);

    MinimalStructMember mst_height;
    mst_height.common().member_id(memberId++);
    mst_height.common().member_flags().TRY_CONSTRUCT1(false); // Unsupported
    mst_height.common().member_flags().TRY_CONSTRUCT2(false); // Unsupported
    mst_height.common().member_flags().IS_EXTERNAL(false); // Unsupported
    mst_height.common().member_flags().IS_OPTIONAL(false);
    mst_height.common().member_flags().IS_MUST_UNDERSTAND(false);
    mst_height.common().member_flags().IS_KEY(false);
    mst_height.common().member_flags().IS_DEFAULT(false); // Doesn't apply
    mst_height.common().member_type_id(*TypeObjectFactory::get_instance()->get_type_identifier("uint32_t", false));


    MD5 height_hash("height");
    for(int i = 0; i < 4; ++i)
    {
        mst_height.detail().name_hash()[i] = height_hash.digest[i];
    }
    type_object->minimal().struct_type().member_seq().emplace_back(mst_height);

    MinimalStructMember mst_width;
    mst_width.common().member_id(memberId++);
    mst_width.common().member_flags().TRY_CONSTRUCT1(false); // Unsupported
    mst_width.common().member_flags().TRY_CONSTRUCT2(false); // Unsupported
    mst_width.common().member_flags().IS_EXTERNAL(false); // Unsupported
    mst_width.common().member_flags().IS_OPTIONAL(false);
    mst_width.common().member_flags().IS_MUST_UNDERSTAND(false);
    mst_width.common().member_flags().IS_KEY(false);
    mst_width.common().member_flags().IS_DEFAULT(false); // Doesn't apply
    mst_width.common().member_type_id(*TypeObjectFactory::get_instance()->get_type_identifier("uint32_t", false));


    MD5 width_hash("width");
    for(int i = 0; i < 4; ++i)
    {
        mst_width.detail().name_hash()[i] = width_hash.digest[i];
    }
    type_object->minimal().struct_type().member_seq().emplace_back(mst_width);

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

    MinimalStructMember mst_transport;
    mst_transport.common().member_id(memberId++);
    mst_transport.common().member_flags().TRY_CONSTRUCT1(false); // Unsupported
    mst_transport.common().member_flags().TRY_CONSTRUCT2(false); // Unsupported
    mst_transport.common().member_flags().IS_EXTERNAL(false); // Unsupported
    mst_transport.common().member_flags().IS_OPTIONAL(false);
    mst_transport.common().member_flags().IS_MUST_UNDERSTAND(false);
    mst_transport.common().member_flags().IS_KEY(false);
    mst_transport.common().member_flags().IS_DEFAULT(false); // Doesn't apply
    mst_transport.common().member_type_id(*TypeObjectFactory::get_instance()->get_type_identifier("uint32_t", false));


    MD5 transport_hash("transport");
    for(int i = 0; i < 4; ++i)
    {
        mst_transport.detail().name_hash()[i] = transport_hash.digest[i];
    }
    type_object->minimal().struct_type().member_seq().emplace_back(mst_transport);


    // Header
    // TODO Inheritance
    //type_object->minimal().struct_type().header().base_type()._d(EK_MINIMAL);
    //type_object->minimal().struct_type().header().base_type().equivalence_hash()[0..13];
    TypeIdentifier identifier;
    identifier._d(EK_MINIMAL);

    eprosima::fastcdr::CdrSizeCalculator calculator(eprosima::fastcdr::CdrVersion::XCDRv1);
    size_t current_alignment {0};
    SerializedPayload_t payload(static_cast<uint32_t>(
        calculator.calculate_serialized_size(type_object->minimal().struct_type(), current_alignment) + 4));
    eprosima::fastcdr::FastBuffer fastbuffer((char*) payload.data, payload.max_size);
    // Fixed endian (Page 221, EquivalenceHash definition of Extensible and Dynamic Topic Types for DDS document)
    eprosima::fastcdr::Cdr ser(
        fastbuffer, eprosima::fastcdr::Cdr::LITTLE_ENDIANNESS,
        eprosima::fastcdr::CdrVersion::XCDRv1); // Object that serializes the data.
    payload.encapsulation = ser.endianness() == eprosima::fastcdr::Cdr::BIG_ENDIANNESS ? CDR_BE : CDR_LE;

    ser << *type_object;
#if FASTCDR_VERSION_MAJOR == 1
    payload.length = (uint32_t)ser.getSerializedDataLength(); //Get the serialized length
#else
    payload.length = (uint32_t)ser.get_serialized_data_length(); //Get the serialized length
#endif // FASTCDR_VERSION_MAJOR == 1
    MD5 objectHash;
    objectHash.update((char*)payload.data, payload.length);
    objectHash.finalize();
    for(int i = 0; i < 14; ++i)
    {
        identifier.equivalence_hash()[i] = objectHash.digest[i];
    }

    TypeObjectFactory::get_instance()->add_type_object("Image", &identifier, type_object);
    delete type_object;
    return TypeObjectFactory::get_instance()->get_type_object("Image", false);
}

const TypeObject* GetCompleteImageObject()
{
    const TypeObject* c_type_object = TypeObjectFactory::get_instance()->get_type_object("Image", true);
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
    CompleteStructMember cst_image;
    cst_image.common().member_id(memberId++);
    cst_image.common().member_flags().TRY_CONSTRUCT1(false); // Unsupported
    cst_image.common().member_flags().TRY_CONSTRUCT2(false); // Unsupported
    cst_image.common().member_flags().IS_EXTERNAL(false); // Unsupported
    cst_image.common().member_flags().IS_OPTIONAL(false);
    cst_image.common().member_flags().IS_MUST_UNDERSTAND(false);
    cst_image.common().member_flags().IS_KEY(false);
    cst_image.common().member_flags().IS_DEFAULT(false); // Doesn't apply
    cst_image.common().member_type_id(*TypeObjectFactory::get_instance()->get_sequence_identifier("uint8_t", 100, true));

    cst_image.detail().name("image");

    type_object->complete().struct_type().member_seq().emplace_back(cst_image);

    CompleteStructMember cst_frame_number;
    cst_frame_number.common().member_id(memberId++);
    cst_frame_number.common().member_flags().TRY_CONSTRUCT1(false); // Unsupported
    cst_frame_number.common().member_flags().TRY_CONSTRUCT2(false); // Unsupported
    cst_frame_number.common().member_flags().IS_EXTERNAL(false); // Unsupported
    cst_frame_number.common().member_flags().IS_OPTIONAL(false);
    cst_frame_number.common().member_flags().IS_MUST_UNDERSTAND(false);
    cst_frame_number.common().member_flags().IS_KEY(false);
    cst_frame_number.common().member_flags().IS_DEFAULT(false); // Doesn't apply
    cst_frame_number.common().member_type_id(*TypeObjectFactory::get_instance()->get_type_identifier("uint32_t", false));


    cst_frame_number.detail().name("frame_number");

    type_object->complete().struct_type().member_seq().emplace_back(cst_frame_number);

    CompleteStructMember cst_frequency;
    cst_frequency.common().member_id(memberId++);
    cst_frequency.common().member_flags().TRY_CONSTRUCT1(false); // Unsupported
    cst_frequency.common().member_flags().TRY_CONSTRUCT2(false); // Unsupported
    cst_frequency.common().member_flags().IS_EXTERNAL(false); // Unsupported
    cst_frequency.common().member_flags().IS_OPTIONAL(false);
    cst_frequency.common().member_flags().IS_MUST_UNDERSTAND(false);
    cst_frequency.common().member_flags().IS_KEY(false);
    cst_frequency.common().member_flags().IS_DEFAULT(false); // Doesn't apply
    cst_frequency.common().member_type_id(*TypeObjectFactory::get_instance()->get_type_identifier("uint32_t", false));


    cst_frequency.detail().name("frequency");

    type_object->complete().struct_type().member_seq().emplace_back(cst_frequency);

    CompleteStructMember cst_height;
    cst_height.common().member_id(memberId++);
    cst_height.common().member_flags().TRY_CONSTRUCT1(false); // Unsupported
    cst_height.common().member_flags().TRY_CONSTRUCT2(false); // Unsupported
    cst_height.common().member_flags().IS_EXTERNAL(false); // Unsupported
    cst_height.common().member_flags().IS_OPTIONAL(false);
    cst_height.common().member_flags().IS_MUST_UNDERSTAND(false);
    cst_height.common().member_flags().IS_KEY(false);
    cst_height.common().member_flags().IS_DEFAULT(false); // Doesn't apply
    cst_height.common().member_type_id(*TypeObjectFactory::get_instance()->get_type_identifier("uint32_t", false));


    cst_height.detail().name("height");

    type_object->complete().struct_type().member_seq().emplace_back(cst_height);

    CompleteStructMember cst_width;
    cst_width.common().member_id(memberId++);
    cst_width.common().member_flags().TRY_CONSTRUCT1(false); // Unsupported
    cst_width.common().member_flags().TRY_CONSTRUCT2(false); // Unsupported
    cst_width.common().member_flags().IS_EXTERNAL(false); // Unsupported
    cst_width.common().member_flags().IS_OPTIONAL(false);
    cst_width.common().member_flags().IS_MUST_UNDERSTAND(false);
    cst_width.common().member_flags().IS_KEY(false);
    cst_width.common().member_flags().IS_DEFAULT(false); // Doesn't apply
    cst_width.common().member_type_id(*TypeObjectFactory::get_instance()->get_type_identifier("uint32_t", false));


    cst_width.detail().name("width");

    type_object->complete().struct_type().member_seq().emplace_back(cst_width);

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

    CompleteStructMember cst_transport;
    cst_transport.common().member_id(memberId++);
    cst_transport.common().member_flags().TRY_CONSTRUCT1(false); // Unsupported
    cst_transport.common().member_flags().TRY_CONSTRUCT2(false); // Unsupported
    cst_transport.common().member_flags().IS_EXTERNAL(false); // Unsupported
    cst_transport.common().member_flags().IS_OPTIONAL(false);
    cst_transport.common().member_flags().IS_MUST_UNDERSTAND(false);
    cst_transport.common().member_flags().IS_KEY(false);
    cst_transport.common().member_flags().IS_DEFAULT(false); // Doesn't apply
    cst_transport.common().member_type_id(*TypeObjectFactory::get_instance()->get_type_identifier("uint32_t", false));


    cst_transport.detail().name("transport");

    type_object->complete().struct_type().member_seq().emplace_back(cst_transport);


    // Header
    type_object->complete().struct_type().header().detail().type_name("Image");
    // TODO inheritance
    TypeIdentifier identifier;
    identifier._d(EK_COMPLETE);

    eprosima::fastcdr::CdrSizeCalculator calculator(eprosima::fastcdr::CdrVersion::XCDRv1);
    size_t current_alignment {0};
    SerializedPayload_t payload(static_cast<uint32_t>(
        calculator.calculate_serialized_size(type_object->complete().struct_type(), current_alignment) + 4));
    eprosima::fastcdr::FastBuffer fastbuffer((char*) payload.data, payload.max_size);
    // Fixed endian (Page 221, EquivalenceHash definition of Extensible and Dynamic Topic Types for DDS document)
    eprosima::fastcdr::Cdr ser(
        fastbuffer, eprosima::fastcdr::Cdr::LITTLE_ENDIANNESS,
        eprosima::fastcdr::CdrVersion::XCDRv1); // Object that serializes the data.
    payload.encapsulation = ser.endianness() == eprosima::fastcdr::Cdr::BIG_ENDIANNESS ? CDR_BE : CDR_LE;

    ser << *type_object;
#if FASTCDR_VERSION_MAJOR == 1
    payload.length = (uint32_t)ser.getSerializedDataLength(); //Get the serialized length
#else
    payload.length = (uint32_t)ser.get_serialized_data_length(); //Get the serialized length
#endif // FASTCDR_VERSION_MAJOR == 1
    MD5 objectHash;
    objectHash.update((char*)payload.data, payload.length);
    objectHash.finalize();
    for(int i = 0; i < 14; ++i)
    {
        identifier.equivalence_hash()[i] = objectHash.digest[i];
    }

    TypeObjectFactory::get_instance()->add_type_object("Image", &identifier, type_object);
    delete type_object;
    return TypeObjectFactory::get_instance()->get_type_object("Image", true);
}
