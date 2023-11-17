/// @file    Vec3.cpp
/// @author  Matthew Green
/// @date    10/27/2023 17:23:08
/// 
/// @section LICENSE
/// 
/// Copyright (c) 2023 Matthew Green - All rights reserved
/// Unauthorized copying of this file, via any medium is strictly prohibited
/// Proprietary and confidential

#include "velecs/Math/Vec3.h"
#include "velecs/Math/Vec2.h"
#include "velecs/Math/Consts.h"

#include <sstream>
#include <algorithm>

namespace velecs {

// Public Fields

const Vec3 Vec3::ZERO         {  0.0f,  0.0f,  0.0f };
const Vec3 Vec3::ONE          {  1.0f,  1.0f,  1.0f };
const Vec3 Vec3::NEG_ONE      { -1.0f, -1.0f, -1.0f };
const Vec3 Vec3::UP           {  0.0f, -1.0f,  0.0f };
const Vec3 Vec3::DOWN         {  0.0f,  1.0f,  0.0f };
const Vec3 Vec3::RIGHT        {  1.0f,  0.0f,  0.0f };
const Vec3 Vec3::LEFT         { -1.0f,  0.0f,  0.0f };
const Vec3 Vec3::FORWARD      {  0.0f,  0.0f, -1.0f };
const Vec3 Vec3::BACKWARD     {  0.0f,  0.0f,  1.0f };
const Vec3 Vec3::POS_INFINITY { FLOAT_POS_INFINITY, FLOAT_POS_INFINITY, FLOAT_POS_INFINITY };
const Vec3 Vec3::NEG_INFINITY { FLOAT_NEG_INFINITY, FLOAT_NEG_INFINITY, FLOAT_NEG_INFINITY };
const Vec3 Vec3::UNIT         = ONE.Normalize();
const Vec3 Vec3::I            {  1.0f,  0.0f,  0.0f };
const Vec3 Vec3::J            {  0.0f,  1.0f,  0.0f };
const Vec3 Vec3::K            {  0.0f,  0.0f,  1.0f };

// Constructors and Destructors

Vec3::Vec3(const float x, const float y, const float z)
    : x(x), y(y), z(z) {}

Vec3::Vec3(const Vec2 vec2)
    : x(vec2.x), y(vec2.y), z(0.0f) {}

Vec3::Vec3(const Vec2 vec2, const float z)
    : x(vec2.x), y(vec2.y), z(z) {}

Vec3::Vec3(const float x, const struct Vec2 vec2)
    : x(x), y(vec2.x), z(vec2.y) {}

// Public Methods

Vec3::operator glm::vec3() const
{
    return glm::vec3(x, y, z);
}

Vec3& Vec3::operator=(const Vec3 other)
{
    x = other.x;
    y = other.y;
    z = other.z;

    return *this; // Return ref to allow chaining assignment operations
}

bool Vec3::operator==(const Vec3 other) const
{
    return x == other.x &&
        y == other.y &&
        z == other.z;
}

bool Vec3::operator!=(const Vec3 other) const
{
    return x != other.x ||
        y != other.y ||
        z != other.z;
}

Vec3 Vec3::operator-() const
{
    return Vec3(-x, -y, -z);
}

Vec3& Vec3::operator+=(const Vec3 other)
{
    x += other.x;
    y += other.y;
    z += other.z;
    return *this;
}

Vec3& Vec3::operator-=(const Vec3 other)
{
    x -= other.x;
    y -= other.y;
    z -= other.z;
    return *this;
}

Vec3& Vec3::operator*=(const float scalar)
{
    x *= scalar;
    y *= scalar;
    z *= scalar;
    return *this;
}

Vec3& Vec3::operator/=(const float scalar)
{
    x /= scalar;
    y /= scalar;
    z /= scalar;
    return *this;
}

unsigned int Vec3::L0Norm() const
{
    return (x != 0 ? 1 : 0) + (y != 0 ? 1 : 0) + (z != 0 ? 1 : 0);
}

float Vec3::L1Norm() const
{
    return std::abs(x) + std::abs(y) + std::abs(z);
}

float Vec3::L2Norm() const
{
    return std::sqrt(x*x + y*y + z*z);
}

Vec3 Vec3::Normalize() const
{
    float magnitude = L2Norm();
    return (magnitude != 0) ? (*this)/magnitude : Vec3::ZERO;
}

Vec3 Vec3::ProjOntoI() const
{
    return Vec3(this->x, 0.0f, 0.0f);
}

Vec3 Vec3::ProjOntoJ() const
{
    return Vec3(0.0f, this->y, 0.0f);
}

Vec3 Vec3::ProjOntoK() const
{
    return Vec3(0.0f, 0.0f, this->z);
}

float Vec3::Dot(const Vec3 a, const Vec3 b)
{
    return a.x * b.x + a.y * b.y + a.z * b.z;
}

Vec3 Vec3::Cross(const Vec3 a, const Vec3 b)
{
    return Vec3
    (
        a.y * b.z - a.z * b.y,
        a.z * b.x - a.x * b.z,
        a.x * b.y - a.y * b.x
    );
}

Vec3 Vec3::Hadamard(const Vec3 a, const Vec3 b)
{
    return Vec3(a.x * b.x, a.y * b.y, a.z * b.z);
}

Vec3 Vec3::Clamp(const Vec3 vec, const Vec3 min, const Vec3 max)
{
    return Vec3
    (
        std::clamp(vec.x, min.x, max.x),
        std::clamp(vec.y, min.y, max.y),
        std::clamp(vec.z, min.z, max.z)
    );
}

Vec3 Vec3::Lerp(const Vec3 a, const Vec3 b, float t)
{
    return Vec3
    (
        a.x + t * (b.x - a.x),
        a.y + t * (b.y - a.y),
        a.z + t * (b.z - a.z)
    );
}

float Vec3::Angle(const Vec3 a, const Vec3 b)
{
    float dotProduct = Dot(a, b);
    float magnitudes = a.L2Norm() * b.L2Norm();
    if (magnitudes == 0) return 0;  // avoid division by zero
    float cosineTheta = dotProduct / magnitudes;
    // Clamp cosineTheta to the range [-1, 1] to avoid NaN due to floating point errors.
    cosineTheta = std::max(-1.0f, std::min(1.0f, cosineTheta));
    return std::acos(cosineTheta);  // result is in radians
}

std::string Vec3::ToString() const
{
    std::ostringstream oss;
    oss << '(' << x << ", " << y << ", " << z << ')';
    return oss.str();
}

Vec3 operator+(const Vec3 lhs, const Vec3 rhs)
{
    return Vec3{lhs.x + rhs.x, lhs.y + rhs.y, lhs.z + rhs.z};
}

Vec3 operator-(const Vec3 lhs, const Vec3 rhs)
{
    return Vec3{lhs.x - rhs.x, lhs.y - rhs.y, lhs.z - rhs.z};
}

Vec3 operator*(const Vec3 lhs, const float rhs)
{
    return Vec3{lhs.x * rhs, lhs.y * rhs, lhs.z * rhs};
}

Vec3 operator/(const Vec3 lhs, const float rhs)
{
    if (rhs == 0)
    {
        throw std::runtime_error("Division by zero error");
    }
    return Vec3{lhs.x / rhs, lhs.y / rhs, lhs.z / rhs};
}

// Protected Fields

// Protected Methods

// Private Fields

// Private Methods

} // namespace velecs
