/// @file    Vec2.cpp
/// @author  Matthew Green
/// @date    10/15/2023 12:36:20
/// 
/// @section LICENSE
/// 
/// Copyright (c) 2023 Matthew Green - All rights reserved
/// Unauthorized copying of this file, via any medium is strictly prohibited
/// Proprietary and confidential

#include "velecs/Math/Vec2.h"
#include "velecs/Math/Vec3.h"
#include "velecs/Math/Consts.h"

#include <sstream>
#include <algorithm>

namespace velecs {

// Public Fields

const Vec2 Vec2::ZERO         {  0.0f,  0.0f };
const Vec2 Vec2::ONE          {  1.0f,  1.0f };
const Vec2 Vec2::NEG_ONE      { -1.0f, -1.0f };
const Vec2 Vec2::UP           {  0.0f, -1.0f };
const Vec2 Vec2::DOWN         {  0.0f,  1.0f };
const Vec2 Vec2::RIGHT        {  1.0f,  0.0f };
const Vec2 Vec2::LEFT         { -1.0f,  0.0f };
const Vec2 Vec2::POS_INFINITY { FLOAT_POS_INFINITY, FLOAT_POS_INFINITY };
const Vec2 Vec2::NEG_INFINITY { FLOAT_NEG_INFINITY, FLOAT_NEG_INFINITY };
const Vec2 Vec2::UNIT         = ONE.Normalize();
const Vec2 Vec2::I            {  1.0f,  0.0f };
const Vec2 Vec2::J            {  0.0f,  1.0f };

// Constructors and Destructors

Vec2::Vec2() : x(0.0f), y(0.0f) {}

Vec2::Vec2(const float x, const float y) : x(x), y(y) {}

Vec2::Vec2(const Vec2 &other) : x(other.x), y(other.y) {}

// Public Methods

Vec2::operator glm::vec2() const
{
    return glm::vec2(x, y);
}

Vec2::operator Vec3() const
{
    return Vec3(*this);
}

Vec2::operator glm::vec3() const
{
    return glm::vec3(x, y, 0.0f);
}

Vec2& Vec2::operator=(const Vec2 other)
{
    x = other.x;
    y = other.y;

    return *this; // Return ref to allow chaining assignment operations
}

bool Vec2::operator==(const Vec2 other) const
{
    return x == other.x &&
        y == other.y;
}

bool Vec2::operator!=(const Vec2 other) const
{
    return x != other.x ||
        y != other.y;
}

Vec2 Vec2::operator-() const
{
    return Vec2(-x, -y);
}

Vec2& Vec2::operator+=(const Vec2 other)
{
    x += other.x;
    y += other.y;

    return *this; // Return ref to allow chaining assignment operations
}

Vec2& Vec2::operator-=(const Vec2 other)
{
    x -= other.x;
    y -= other.y;

    return *this; // Return ref to allow chaining assignment operations
}

Vec2& Vec2::operator*=(const float scalar)
{
    x *= scalar;
    y *= scalar;

    return *this; // Return ref to allow chaining assignment operations
}

Vec2& Vec2::operator/=(const float scalar)
{
    x /= scalar;
    y /= scalar;

    return *this; // Return ref to allow chaining assignment operations
}

unsigned int Vec2::L0Norm() const
{
    return (x != 0 ? 1 : 0) + (y != 0 ? 1 : 0);
}

float Vec2::L1Norm() const
{
    return fabs(x) + fabs(y);
}

float Vec2::L2Norm() const
{
    return sqrt(x * x + y * y);
}

Vec2 Vec2::Normalize() const
{
    float magnitude = L2Norm();
    return (magnitude != 0) ? (*this)/magnitude : Vec2::ZERO;
}

Vec2 Vec2::ProjOntoI() const
{
    return Vec2(this->x, 0.0f);
}

Vec2 Vec2::ProjOntoJ() const
{
    return Vec2(0.0f, this->y);
}

float Vec2::Dot(const Vec2 a, const Vec2 b)
{
    return a.x * b.x + a.y * b.y;
}

float Vec2::Cross(const Vec2 a, const Vec2 b)
{
    return a.x * b.y - a.y * b.x;
}

Vec2 Vec2::Hadamard(const Vec2 a, const Vec2 b)
{
    return Vec2(a.x * b.x, a.y * b.y);
}

Vec2 Vec2::Clamp(const Vec2 vec, const Vec2 min, const Vec2 max)
{
    return Vec2
    (
        std::clamp(vec.x, min.x, max.x),
        std::clamp(vec.y, min.y, max.y)
    );
}

Vec2 Vec2::Lerp(const Vec2 vec1, const Vec2 vec2, float t)
{
    return Vec2
    (
        vec1.x + t * (vec2.x - vec1.x),
        vec1.y + t * (vec2.y - vec1.y)
    );
}

float Vec2::Angle(const Vec2 a, const Vec2 b)
{
    float dotProduct = Dot(a, b);
    float magnitudes = a.L2Norm() * b.L2Norm();
    if (magnitudes == 0) return 0;  // avoid division by zero
    float cosineTheta = dotProduct / magnitudes;
    return std::acos(cosineTheta);  // result is in radians
}

std::string Vec2::ToString() const
{
    std::ostringstream oss;
    oss << '(' << x << ", " << y << ')';
    return oss.str();
}

Vec2 operator+(const Vec2 lhs, const Vec2 rhs)
{
    return Vec2(lhs.x + rhs.x, lhs.y + rhs.x);
}

Vec2 operator-(const Vec2 lhs, const Vec2 rhs)
{
    return Vec2{lhs.x - rhs.x, lhs.y - rhs.y};
}

Vec2 operator*(const Vec2 lhs, const float rhs)
{
    return Vec2{lhs.x * rhs, lhs.y * rhs};
}

Vec2 operator/(const Vec2 lhs, const float rhs)
{
    if (rhs == 0)
    {
        throw std::runtime_error("Division by zero error");
    }
    return Vec2{lhs.x / rhs, lhs.y / rhs};
}

// Protected Fields

// Protected Methods

// Private Fields

// Private Methods

} // namespace $defaultnamespace$::
