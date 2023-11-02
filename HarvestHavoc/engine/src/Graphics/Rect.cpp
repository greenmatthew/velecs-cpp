/// \file    Rect.cpp
/// \author  Matthew Green
/// \date    11/01/2023 19:26:53
/// 
/// \section LICENSE
/// 
/// Copyright (c) 2023 Matthew Green - All rights reserved
/// Unauthorized copying of this file, via any medium is strictly prohibited
/// Proprietary and confidential

#include "Graphics/Rect.h"

namespace engine {

// Public Fields

// Constructors and Destructors

/// \brief Constructor.
Rect::Rect(const Vec2 min, const Vec2 max)
	: min(min), max(max) {}

/// \brief Constructor.
Rect::Rect(const float left, const float bottom, const float right, const float top)
	: min(Vec2{ left, bottom }), max(Vec2{ right, top }) {}

// Public Methods

float Rect::GetWidth() const
{
    return max.x - min.x;
}

float Rect::GetLength() const
{
    return max.y - min.y;
}

float Rect::GetArea() const
{
    return GetWidth() * GetLength();
}

float Rect::GetPerimeter() const
{
    return 2 * (GetWidth() + GetLength());
}

Vec2 Rect::GetCenter() const
{
    return Vec2((min.x + max.x) / 2, (min.y + max.y) / 2);
}

bool Rect::Contains(const Vec2& point) const
{
    return point.x >= min.x && point.x <= max.x &&
           point.y >= min.y && point.y <= max.y;
}

bool Rect::Intersects(const Rect& other) const
{
    return max.x >= other.min.x && min.x <= other.max.x &&
           max.y >= other.min.y && min.y <= other.max.y;
}

// Protected Fields

// Protected Methods

// Private Fields

// Private Methods

} // namespace engine
