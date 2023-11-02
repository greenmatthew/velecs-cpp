/// \file    Rect.h
/// \author  Matthew Green
/// \date    11/01/2023 19:23:20
/// 
/// \section LICENSE
/// 
/// Copyright (c) 2023 Matthew Green - All rights reserved
/// Unauthorized copying of this file, via any medium is strictly prohibited
/// Proprietary and confidential

#pragma once

#include "Math/Vec2.h"

namespace engine {

/// \class Rect
/// \brief Represents a 2D rectangle defined by minimum and maximum points.
///
/// This class encapsulates a 2D rectangle defined by two points: the minimum point (bottom-left) and the maximum point (top-right).
/// It provides constructors for specifying the rectangle's dimensions and utility methods for working with the rectangle.
struct Rect {
public:
    // Enums

    // Public Fields

    Vec2 min; /// \brief Minimum point (bottom-left corner) of the rectangle.
    Vec2 max; /// \brief Maximum point (top-right corner) of the rectangle.

    // Constructors and Destructors
    
    /// \brief Constructs a rectangle with the specified minimum and maximum points.
    /// 
    /// \param min The minimum point (bottom-left corner) of the rectangle.
    /// \param max The maximum point (top-right corner) of the rectangle.
    Rect(const Vec2 min, const Vec2 max);

    /// \brief Constructs a rectangle with the specified dimensions.
    /// 
    /// \param left The x-coordinate of the bottom-left corner of the rectangle.
    /// \param bottom The y-coordinate of the bottom-left corner of the rectangle.
    /// \param right The x-coordinate of the top-right corner of the rectangle.
    /// \param top The y-coordinate of the top-right corner of the rectangle.
    Rect(const float left, const float bottom, const float right, const float top);
    
    /// \brief Default deconstructor.
    ~Rect() = default;

    // Public Methods

    /// \brief Computes and returns the width of the rectangle.
    ///
    /// This method calculates the width of the rectangle by subtracting the x-coordinate of the minimum point from the x-coordinate of the maximum point.
    /// \return The width of the rectangle.
    float GetWidth() const;

    /// \brief Computes and returns the length of the rectangle.
    ///
    /// This method calculates the length of the rectangle by subtracting the y-coordinate of the minimum point from the y-coordinate of the maximum point.
    /// \return The length of the rectangle.
    float GetLength() const;

    /// \brief Computes and returns the area of the rectangle.
    /// \return The area of the rectangle.
    float GetArea() const;

    /// \brief Computes and returns the perimeter of the rectangle.
    /// \return The perimeter of the rectangle.
    float GetPerimeter() const;

    /// \brief Computes and returns the center point of the rectangle.
    /// \return The center point of the rectangle.
    Vec2 GetCenter() const;

    /// \brief Checks if a point is within the rectangle.
    /// \param[in] point The point to check.
    /// \return True if the point is within the rectangle, false otherwise.
    bool Contains(const Vec2& point) const;

    /// \brief Checks if another rectangle intersects with this rectangle.
    /// \param[in] other The other rectangle to check.
    /// \return True if the rectangles intersect, false otherwise.
    bool Intersects(const Rect& other) const;

protected:
    // Protected Fields

    // Protected Methods

private:
    // Private Fields

    // Private Methods
};

} // namespace engine
