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
 * @file Image.h
 * This header file contains the declaration of the described types in the IDL file.
 *
 * This file was generated by the tool fastddsgen.
 */

#ifndef _FAST_DDS_GENERATED_IMAGE_H_
#define _FAST_DDS_GENERATED_IMAGE_H_

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
#if defined(IMAGE_SOURCE)
#define IMAGE_DllAPI __declspec( dllexport )
#else
#define IMAGE_DllAPI __declspec( dllimport )
#endif // IMAGE_SOURCE
#else
#define IMAGE_DllAPI
#endif  // EPROSIMA_USER_DLL_EXPORT
#else
#define IMAGE_DllAPI
#endif // _WIN32

namespace eprosima {
namespace fastcdr {
class Cdr;
class CdrSizeCalculator;
} // namespace fastcdr
} // namespace eprosima





/*!
 * @brief This class represents the structure Image defined by the user in the IDL file.
 * @ingroup Image
 */
class Image
{
public:

    /*!
     * @brief Default constructor.
     */
    eProsima_user_DllExport Image();

    /*!
     * @brief Default destructor.
     */
    eProsima_user_DllExport ~Image();

    /*!
     * @brief Copy constructor.
     * @param x Reference to the object Image that will be copied.
     */
    eProsima_user_DllExport Image(
            const Image& x);

    /*!
     * @brief Move constructor.
     * @param x Reference to the object Image that will be copied.
     */
    eProsima_user_DllExport Image(
            Image&& x) noexcept;

    /*!
     * @brief Copy assignment.
     * @param x Reference to the object Image that will be copied.
     */
    eProsima_user_DllExport Image& operator =(
            const Image& x);

    /*!
     * @brief Move assignment.
     * @param x Reference to the object Image that will be copied.
     */
    eProsima_user_DllExport Image& operator =(
            Image&& x) noexcept;

    /*!
     * @brief Comparison operator.
     * @param x Image object to compare.
     */
    eProsima_user_DllExport bool operator ==(
            const Image& x) const;

    /*!
     * @brief Comparison operator.
     * @param x Image object to compare.
     */
    eProsima_user_DllExport bool operator !=(
            const Image& x) const;

    /*!
     * @brief This function copies the value in member image
     * @param _image New value to be copied in member image
     */
    eProsima_user_DllExport void image(
            const std::vector<uint8_t>& _image);

    /*!
     * @brief This function moves the value in member image
     * @param _image New value to be moved in member image
     */
    eProsima_user_DllExport void image(
            std::vector<uint8_t>&& _image);

    /*!
     * @brief This function returns a constant reference to member image
     * @return Constant reference to member image
     */
    eProsima_user_DllExport const std::vector<uint8_t>& image() const;

    /*!
     * @brief This function returns a reference to member image
     * @return Reference to member image
     */
    eProsima_user_DllExport std::vector<uint8_t>& image();


    /*!
     * @brief This function sets a value in member frame_number
     * @param _frame_number New value for member frame_number
     */
    eProsima_user_DllExport void frame_number(
            uint32_t _frame_number);

    /*!
     * @brief This function returns the value of member frame_number
     * @return Value of member frame_number
     */
    eProsima_user_DllExport uint32_t frame_number() const;

    /*!
     * @brief This function returns a reference to member frame_number
     * @return Reference to member frame_number
     */
    eProsima_user_DllExport uint32_t& frame_number();


    /*!
     * @brief This function sets a value in member frequency
     * @param _frequency New value for member frequency
     */
    eProsima_user_DllExport void frequency(
            uint32_t _frequency);

    /*!
     * @brief This function returns the value of member frequency
     * @return Value of member frequency
     */
    eProsima_user_DllExport uint32_t frequency() const;

    /*!
     * @brief This function returns a reference to member frequency
     * @return Reference to member frequency
     */
    eProsima_user_DllExport uint32_t& frequency();


    /*!
     * @brief This function sets a value in member height
     * @param _height New value for member height
     */
    eProsima_user_DllExport void height(
            uint32_t _height);

    /*!
     * @brief This function returns the value of member height
     * @return Value of member height
     */
    eProsima_user_DllExport uint32_t height() const;

    /*!
     * @brief This function returns a reference to member height
     * @return Reference to member height
     */
    eProsima_user_DllExport uint32_t& height();


    /*!
     * @brief This function sets a value in member width
     * @param _width New value for member width
     */
    eProsima_user_DllExport void width(
            uint32_t _width);

    /*!
     * @brief This function returns the value of member width
     * @return Value of member width
     */
    eProsima_user_DllExport uint32_t width() const;

    /*!
     * @brief This function returns a reference to member width
     * @return Reference to member width
     */
    eProsima_user_DllExport uint32_t& width();


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

    std::vector<uint8_t> m_image;
    uint32_t m_frame_number{0};
    uint32_t m_frequency{0};
    uint32_t m_height{0};
    uint32_t m_width{0};
    uint64_t m_subscriber_initalize_time{0};
    uint64_t m_publisher_send_time{0};
    uint64_t m_subscriber_recieve_time{0};

};

#endif // _FAST_DDS_GENERATED_IMAGE_H_



