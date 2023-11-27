/// @file    Color32.cpp
/// @author  Matthew Green
/// @date    10/26/2023 15:26:29
/// 
/// @section LICENSE
/// 
/// Copyright (c) 2023 Matthew Green - All rights reserved
/// Unauthorized copying of this file, via any medium is strictly prohibited
/// Proprietary and confidential

#include "velecs/Graphics/Color32.h"

#include <cassert>
#include <sstream>
#include <iomanip>

namespace velecs {

std::ostream& operator<<(std::ostream& os, const Color32 color)
{
    os << color.ToString();
    return os;
}

// Public Fields

const Color32 Color32::RED{255U, 0U, 0U};
const Color32 Color32::GREEN{0U, 255U, 0U};
const Color32 Color32::BLUE{0U, 0U, 255U};
const Color32 Color32::CYAN{0U, 255U, 255U};
const Color32 Color32::MAGENTA{255U, 0U, 255U};
const Color32 Color32::YELLOW{255U, 255U, 0U};
const Color32 Color32::GRAY{128U, 128U, 128U};
const Color32 Color32::GREY{GRAY};
const Color32 Color32::WHITE{255U, 255U, 255U};
const Color32 Color32::BLACK{0U, 0U, 0U};
const Color32 Color32::ORANGE{255U, 165U, 0U};
const Color32 Color32::PINK{255U, 192U, 203U};
const Color32 Color32::PURPLE{128U, 0U, 128U};
const Color32 Color32::BROWN{139U, 69U, 19U};
const Color32 Color32::GOLD{255U, 215U, 0U};
const Color32 Color32::SILVER{192U, 192U, 192U};
const Color32 Color32::BEIGE{245U, 245U, 220U};
const Color32 Color32::NAVY{0U, 0U, 128U};
const Color32 Color32::MAROON{128U, 0U, 0U};
const Color32 Color32::OLIVE{128U, 128U, 0U};
const Color32 Color32::LIME_GREEN{0U, 255U, 0U};
const Color32 Color32::INDIGO{75U, 0U, 130U};
const Color32 Color32::VIOLET{238U, 130U, 238U};

// Constructors and Destructors

Color32::Color32()
    : r(255U), g(0U), b(255U), a(255U) {}

Color32::Color32(const Color32& color)
    : r(color.r), g(color.g), b(color.b), a(color.a) {}

// Public Methods

Color32 Color32::FromUInt8(const uint8_t r, const uint8_t g, const uint8_t b, const uint8_t a /*= 255U*/)
{
    return Color32{r, g, b, a};
}

Color32 Color32::FromUInt32(const uint32_t value)
{
    uint8_t r = (value >> 24) & 0xFF; // Shift by 24 bits and mask out the other components
    uint8_t g = (value >> 16) & 0xFF; // Shift by 16 bits and mask out the other components
    uint8_t b = (value >> 8) & 0xFF;  // Shift by 8 bits and mask out the other components
    uint8_t a = value & 0xFF;         // Mask out all but the last byte

    return Color32(r, g, b, a);
}

Color32 Color32::FromHex(const std::string& hexCode)
{
    size_t length = hexCode.length();
    bool hasHash = hexCode[0] == '#';
    
    // Check if the length is valid (6 or 8 hex digits, +1 if there's a '#')
    if (!((length == 7 && hasHash) || (length == 9 && hasHash) ||
            (length == 6 && !hasHash) || (length == 8 && !hasHash))) {
        throw std::invalid_argument("Invalid hex code length");
    }

    unsigned int hexValue = std::stoul(hexCode.substr(hasHash ? 1 : 0), nullptr, 16);

    uint8_t r = (hexValue >> 24) & 0xFF;
    uint8_t g = (hexValue >> 16) & 0xFF;
    uint8_t b = (hexValue >> 8) & 0xFF;
    uint8_t a = (length == 8 || length == 9) ? (hexValue & 0xFF) : 0xFF;

    return Color32(r, g, b, a);
}

Color32 Color32::FromFloat(const float r, const float g, const float b, const float a /*= 1.0f*/)
{
    return Color32
    (
        static_cast<uint8_t>(r * 255),
        static_cast<uint8_t>(g * 255),
        static_cast<uint8_t>(b * 255),
        static_cast<uint8_t>(a * 255)
    );
}

Color32::operator glm::vec4() const
{
    return glm::vec4
    {
        r/255.0f,
        g/255.0f,
        b/255.0f,
        a/255.0f,
    };
}

uint8_t& Color32::operator[](const std::size_t index)
{
    assert(index < 4);  // Ensure index is within bounds
    return (&r)[index];
}

const uint8_t& Color32::operator[](const std::size_t index) const
{
    assert(index < 4);  // Ensure index is within bounds
    return (&r)[index];
}

Color32& Color32::operator=(const Color32 other)
{
    this->r = other.r;
    this->g = other.g;
    this->b = other.b;
    this->a = other.a;
    return *this;
}

std::string Color32::ToString() const
{
    std::ostringstream oss;
    oss << "RGBA(" << static_cast<int>(r) << ", " << static_cast<int>(g) << ", " << static_cast<int>(b) << ", " << static_cast<int>(a) << ')';
    return oss.str(); 
}

std::string Color32::ToStringNormalized() const
{
    std::ostringstream oss;
    oss << std::fixed << std::setprecision(4);  // Set fixed-point notation with 4 decimal places
    oss << "RGBA(" << r/255.0f << ", " << g/255.0f << ", " << b/255.0f << ", " << a/255.0f << ')';
    return oss.str(); 
}

// Protected Fields

// Protected Methods

// Private Fields

// Constructor

Color32::Color32(const uint8_t r, const uint8_t g, const uint8_t b, const uint8_t a /*= 255U*/)
    : r(r), g(g), b(b), a(a) {}

// Private Methods

} // namespace velecs
