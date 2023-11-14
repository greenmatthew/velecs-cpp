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

#include <sstream>
#include <algorithm>
#include <exception>

namespace velecs {

// Public Fields

// Constructors and Destructors

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

Vec2& Vec2::operator=(const Vec2& other)
{
    if (this != &other) // Self assignment guard
    {
        x = other.x;
        y = other.y;
    }

    return *this; // Return ref to allow chaining assignment operations
}

bool Vec2::operator==(const Vec2& other) const
{
    return x == other.x && y == other.y;
}

bool Vec2::operator!=(const Vec2& other) const
{
    return x != other.x || y != other.y;
}

Vec2 Vec2::operator-() const
{
    return Vec2(-x, -y);
}

Vec2 Vec2::operator+(const Vec2& other) const
{
    return Vec2(x + other.x, y + other.y);
}

Vec2 Vec2::operator-(const Vec2& other) const
{
    return Vec2(x - other.x, y - other.y);
}

Vec2 Vec2::operator*(const float scalar) const
{
    return Vec2(x * scalar, y * scalar);
}

Vec2 Vec2::operator/(const float scalar) const
{
    return Vec2(x / scalar, y / scalar);
}

Vec2& Vec2::operator+=(const Vec2& other)
{
    x += other.x;
    y += other.y;

    return *this; // Return ref to allow chaining assignment operations
}

Vec2& Vec2::operator-=(const Vec2& other)
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
    return (magnitude != 0) ? Vec2(x / magnitude, y / magnitude) : Vec2(0, 0);
}

Vec2 Vec2::ProjOntoI() const
{
    return Vec2(this->x, 0.0f);
}

Vec2 Vec2::ProjOntoJ() const
{
    return Vec2(0.0f, this->y);
}

float Vec2::Dot(const Vec2& a, const Vec2& b)
{
    return a.x * b.x + a.y * b.y;
}

float Vec2::Cross(const Vec2& a, const Vec2& b)
{
    return a.x * b.y - a.y * b.x;
}

Vec2 Vec2::Hadamard(const Vec2& a, const Vec2& b)
{
    return Vec2(a.x * b.x, a.y * b.y);
}

Vec2 Vec2::Clamp(const Vec2& vec, const Vec2& min, const Vec2& max)
{
    return Vec2(
        std::clamp(vec.x, min.x, max.x),
        std::clamp(vec.y, min.y, max.y)
    );
}

Vec2 Vec2::Lerp(const Vec2& vec1, const Vec2& vec2, float t)
{
    return Vec2(
        vec1.x + t * (vec2.x - vec1.x),
        vec1.y + t * (vec2.y - vec1.y)
    );
}

std::string Vec2::ToString() const
{
    std::ostringstream oss;
    oss << '(' << x << ", " << y << ')';
    return oss.str();
}

// Protected Fields

// Protected Methods

// Private Fields

// Private Methods

} // namespace $defaultnamespace$::
