/// \file    Vec3.cpp
/// \author  Matthew Green
/// \date    10/27/2023 17:23:08
/// 
/// \section LICENSE
/// 
/// Copyright (c) 2023 Matthew Green - All rights reserved
/// Unauthorized copying of this file, via any medium is strictly prohibited
/// Proprietary and confidential

#include "Math/Vec3.h"
#include "Math/Vec2.h"
#include "Math/Consts.h"


namespace engine {

// Public Fields

const Vec3 Vec3::ZERO         {  0.0f,  0.0f,  0.0f };
const Vec3 Vec3::ONE          {  1.0f,  1.0f,  1.0f };
const Vec3 Vec3::NEG_ONE      { -1.0f, -1.0f, -1.0f };
const Vec3 Vec3::UP           {  0.0f,  1.0f,  0.0f };
const Vec3 Vec3::DOWN         {  0.0f, -1.0f,  0.0f };
const Vec3 Vec3::RIGHT        {  1.0f,  0.0f,  0.0f };
const Vec3 Vec3::LEFT         { -1.0f,  0.0f,  0.0f };
const Vec3 Vec3::FORWARD      {  0.0f,  0.0f, -1.0f };
const Vec3 Vec3::BACKWARD     {  0.0f,  0.0f,  1.0f };
const Vec3 Vec3::POS_INFINITY { FLOAT_POS_INFINITY, FLOAT_POS_INFINITY, FLOAT_POS_INFINITY };
const Vec3 Vec3::NEG_INFINITY { FLOAT_NEG_INFINITY, FLOAT_NEG_INFINITY, FLOAT_NEG_INFINITY };

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

// Protected Fields

// Protected Methods

// Private Fields

// Private Methods

} // namespace engine
