/// \file    Color32.h
/// \author  Matthew Green
/// \date    10/26/2023 15:00:14
/// 
/// \section LICENSE
/// 
/// Copyright (c) 2023 Matthew Green - All rights reserved
/// Unauthorized copying of this file, via any medium is strictly prohibited
/// Proprietary and confidential

#pragma once

#include <cstdint>
#include <iostream>

namespace velecs {

/// \class Color32
/// \brief Brief description.
///
/// Rest of description.
struct Color32 {
public:
    // Enums

    // Public Fields

    static const Color32 RED;
    static const Color32 GREEN;
    static const Color32 BLUE;
    static const Color32 CYAN;
    static const Color32 MAGENTA;
    static const Color32 YELLOW;
    static const Color32 GRAY;  // more common US spelling
    static const Color32 GREY;  // more common UK spelling
    static const Color32 WHITE;
    static const Color32 BLACK;
    static const Color32 ORANGE;
    static const Color32 PINK;
    static const Color32 PURPLE;
    static const Color32 BROWN;
    static const Color32 GOLD;
    static const Color32 SILVER;
    static const Color32 BEIGE;
    static const Color32 NAVY;
    static const Color32 MAROON;
    static const Color32 OLIVE;
    static const Color32 LIME_GREEN;
    static const Color32 INDIGO;
    static const Color32 VIOLET;

    uint8_t r; /// \brief The red channel.
    uint8_t g; /// \brief The green channel.
    uint8_t b; /// \brief The blue channel.
    uint8_t a; /// \brief The alpha channel.

    // Constructors and Destructors

    Color32();
    
    /// \brief Default deconstructor.
    ~Color32() = default;

    // Public Methods

    /// \brief Constructs a Color32 with specified channel values.
    /// \param[in] r Red channel value.
    /// \param[in] g Green channel value.
    /// \param[in] b Blue channel value.
    /// \param[in] a Alpha channel value (default is 255).
    static Color32 FromUInt8(const uint8_t r, const uint8_t g, const uint8_t b, const uint8_t a = 255U);

    /// \brief Constructs a Color32 with specified channel values.
    /// \param[in] r Red channel value.
    /// \param[in] g Green channel value.
    /// \param[in] b Blue channel value.
    /// \param[in] a Alpha channel value (default is 1.0).
    static Color32 FromFloat(const float r, const float g, const float b, const float a = 1.0f);

    static Color32 FromHSV(const float h, const float s, const float v, const float a = 1.0f);

    /// \brief Overloaded subscript operator for array-like access to color components.
    /// \param[in] index Index of the color component (0 for red, 1 for green, 2 for blue, 3 for alpha).
    /// \return Reference to the specified color component.
    uint8_t& operator[](const std::size_t index);

    /// \brief Const overloaded subscript operator for array-like access to color components.
    /// \param[in] index Index of the color component (0 for red, 1 for green, 2 for blue, 3 for alpha).
    /// \return Const reference to the specified color component.
    const uint8_t& operator[](const std::size_t index) const;

    bool operator==(const Color32 other) const;
    bool operator!=(const Color32 other) const;

    Color32& operator+=(const Color32 other);
    Color32 operator+(const Color32 other) const;
    Color32& operator-=(const Color32 other);
    Color32 operator-(const Color32 other) const;
    Color32& operator*=(const Color32 other);
    Color32 operator*(const Color32 other) const;
    Color32& operator/=(const Color32 other);
    Color32 operator/(const Color32 other) const;

    static void Clamp(const Color32 value, const Color32 min, const Color32 max);
    static Color32 Lerp(const Color32 start, const Color32 end, float t);

    static Color32 AdditiveBlend(const Color32 color1, const Color32 color2);
    static Color32 SubtractiveBlend(const Color32 color1, const Color32 color2);
    static Color32 MultiplyBlend(const Color32 color1, const Color32 color2);
    static Color32 ScreenBlend(const Color32 color1, const Color32 color2);

    static Color32 AlphaBlend(const Color32 src, const Color32 dst);

    void Normalize();
    void ToHSV(float& h, float& s, float& v, float& a) const;

    std::string ToString() const;
    std::string ToStringNormalized() const;

    friend std::ostream& operator<<(std::ostream& os, const Color32 color);

protected:
    // Protected Fields

    // Protected Methods

private:
    // Private Fields

    // Constructor

    /// \brief Constructs a Color32 with specified channel values.
    /// \param[in] r Red channel value.
    /// \param[in] g Green channel value.
    /// \param[in] b Blue channel value.
    /// \param[in] a Alpha channel value (default is 255).
    Color32(const uint8_t r, const uint8_t g, const uint8_t b, const uint8_t a = 255U);

    // Private Methods
};

std::ostream& operator<<(std::ostream& os, const Color32 color);

} // namespace velecs
