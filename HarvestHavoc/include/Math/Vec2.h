/// \file    Vec2.h
/// \author  Matthew Green
/// \date    10/15/2023 12:36:20
/// 
/// \section LICENSE
/// 
/// Copyright (c) 2023 Matthew Green - All rights reserved
/// Unauthorized copying of this file, via any medium is strictly prohibited
/// Proprietary and confidential

#pragma once

#include "Math/Consts.h"

#include <string>
#include <ostream>

namespace HarvestHavoc::Math {

/// \struct Vec2
/// \brief A 2D vector structure for representing points or vectors in 2D space.
struct Vec2
{
public:
    float x;  /// \brief The x-coordinate.
    float y;  /// \brief The y-coordinate.

    /// \brief Constructs a Vec2 with the specified coordinates.
    /// \param[in] x The x-coordinate.
    /// \param[in] y The y-coordinate.
    Vec2(const float x, const float y);

    /// \brief Copy constructor. Constructs a new Vec2 with the same values as the specified Vec2.
    /// \param[in] other The Vec2 to copy.
    Vec2(const Vec2& other);

    /// \brief Default deconstructor.
    ~Vec2() = default;

    /// \brief Assigns the values of another Vec2 object to this Vec2 object.
    /// \param[in] other The other Vec2 object whose values will be assigned to this Vec2 object.
    /// \return A reference to this Vec2 object, after the assignment.
    Vec2& operator=(const Vec2& other);

    /// \brief Checks if this Vec2 is equal to the specified Vec2.
    /// \param[in] other The Vec2 to compare with.
    /// \return True if the Vec2s are equal, false otherwise.
    bool operator==(const Vec2& other) const;

    /// \brief Checks if this Vec2 is not equal to the specified Vec2.
    /// \param[in] other The Vec2 to compare with.
    /// \return True if the Vec2s are not equal, false otherwise.
    bool operator!=(const Vec2& other) const;

    /// \brief Negates this Vec2 object, producing a new Vec2 object with the negated values.
    /// \return A new Vec2 object with the negated values of this Vec2 object.
    Vec2 operator-() const;

    /// \brief Adds another Vec2 to this Vec2.
    /// \param[in] other The other Vec2.
    /// \return A new Vec2 that is the sum of this Vec2 and the other Vec2.
    Vec2 operator+(const Vec2& other) const;

    /// \brief Subtracts another Vec2 from this Vec2.
    /// \param[in] other The other Vec2.
    /// \return A new Vec2 that is the difference of this Vec2 and the other Vec2.
    Vec2 operator-(const Vec2& other) const;

    /// \brief Multiplies this Vec2 by a scalar.
    /// \param[in] scalar The scalar value.
    /// \return A new Vec2 that is the product of this Vec2 and the scalar.
    Vec2 operator*(const float scalar) const;

    friend Vec2 operator*(float scalar, const Vec2& vec);

    /// \brief Divides this Vec2 by a scalar.
    /// \param[in] scalar The scalar value.
    /// \return A new Vec2 that is the quotient of this Vec2 and the scalar.
    Vec2 operator/(const float scalar) const;

    friend Vec2 operator/(float scalar, const Vec2& vec);

    /// \brief Adds another Vec2 to this Vec2 and assigns the result to this Vec2.
    /// \param[in] other The other Vec2.
    /// \return A reference to this Vec2.
    Vec2& operator+=(const Vec2& other);

    /// \brief Subtracts another Vec2 from this Vec2 and assigns the result to this Vec2.
    /// \param[in] other The other Vec2.
    /// \return A reference to this Vec2.
    Vec2& operator-=(const Vec2& other);

    /// \brief Multiplies this Vec2 by a scalar and assigns the result to this Vec2.
    /// \param[in] scalar The scalar value.
    /// \return A reference to this Vec2.
    Vec2& operator*=(const float scalar);

    /// \brief Divides this Vec2 by a scalar and assigns the result to this Vec2.
    /// \param[in] scalar The scalar value.
    /// \return A reference to this Vec2.
    Vec2& operator/=(const float scalar);

    /// \brief Computes the L0 norm of this Vec2, which is the count of non-zero components.
    /// \returns The L0 norm.
    unsigned int L0Norm() const;

    /// \brief Computes the L1 norm of this Vec2, which is the sum of the absolute values of the components.
    /// \returns The L1 norm.
    float L1Norm() const;

    /// \brief Computes the L2 norm (magnitude) of this Vec2.
    /// \returns The L2 norm.
    float L2Norm() const;

    /// \brief Alias for L2Norm, computes the L2 norm (magnitude) of this Vec2.
    /// \returns The L2 norm.
    inline float Norm() const { return L2Norm(); }

    /// \brief Alias for L2Norm, computes the L2 norm (magnitude) of this Vec2.
    /// \returns The L2 norm.
    inline float Magnitude() const { return L2Norm(); }

    /// \brief Normalizes this Vec2, making its magnitude equal to 1.
    /// \returns The normalized Vec2.
    Vec2 Normalize() const;

    /// \brief Projects the vector onto the i basis vector (x-axis).
    /// \returns The projection of the vector onto the i basis vector.
    Vec2 ProjOntoI() const;

    /// \brief Projects the vector onto the j basis vector (y-axis).
    /// \returns The projection of the vector onto the j basis vector.
    Vec2 ProjOntoJ() const;

    /// \brief Computes the dot product of two Vec2 objects.
    /// \param a The first Vec2 object.
    /// \param b The second Vec2 object.
    /// \returns The dot product of a and b.
    static float Dot(const Vec2& a, const Vec2& b);

    /// \brief Computes the cross product of two Vec2 objects.
    /// \param a The first Vec2 object.
    /// \param b The second Vec2 object.
    /// \returns The cross product of a and b.
    static float Cross(const Vec2& a, const Vec2& b);

    /// \brief Computes the Hadamard product of two Vec2 objects.
    /// \param a The first Vec2 object.
    /// \param b The second Vec2 object.
    /// \returns The Hadamard product of a and b.
    static Vec2 Hadamard(const Vec2& a, const Vec2& b);

    /// \brief Alias for Hadamard, computes the element-wise multiplication of two Vec2s.
    /// \param a The first Vec2.
    /// \param b The second Vec2.
    /// \returns The element-wise multiplication of the two Vec2s.
    inline static Vec2 ElementwiseMultiply(const Vec2& a, const Vec2& b) { return Hadamard(a, b); }

    /// \brief Clamps the components of a Vec2 between the corresponding components of two other Vec2s.
    /// \param vec The Vec2 to clamp.
    /// \param min The Vec2 representing the minimum values.
    /// \param max The Vec2 representing the maximum values.
    /// \returns The clamped Vec2.
    static Vec2 Clamp(const Vec2& vec, const Vec2& min, const Vec2& max);

    /// \brief Computes a linear interpolation between two Vec2s.
    /// \param vec1 The first Vec2.
    /// \param vec2 The second Vec2.
    /// \param t The interpolation factor. A value of 0 returns vec1, and a value of 1 returns vec2.
    /// \returns The interpolated Vec2.
    static Vec2 Lerp(const Vec2& vec1, const Vec2& vec2, float t);

    /// \brief Computes the angle between two vectors in radians.
    /// \param a The first vector.
    /// \param b The second vector.
    /// \returns The angle between the vectors in radians.
    static float Angle(const Vec2& a, const Vec2& b)
    {
        float dotProduct = Dot(a, b);
        float magnitudes = a.L2Norm() * b.L2Norm();
        if (magnitudes == 0) return 0;  // avoid division by zero
        float cosineTheta = dotProduct / magnitudes;
        return std::acos(cosineTheta);  // result is in radians
    }

    /// \brief Computes the angle between two vectors in degrees.
    /// \param a The first vector.
    /// \param b The second vector.
    /// \returns The angle between the vectors in degrees.
    static float AngleDeg(const Vec2& a, const Vec2& b)
    {
        return Angle(a, b) * (180.0f / PI);  // convert radians to degrees
    }

    /// \brief Converts the Vec2 to a string representation.
    /// \returns A string representation of the Vec2.
    std::string ToString() const;

    /// \brief Gets a Vec2 object with both coordinates set to 1.
    /// \returns A Vec2 object.
    static Vec2 one()
    {
        static const Vec2 instance(1.0f, 1.0f);
        return instance;
    }

    /// \brief Gets a Vec2 object with both coordinates set to 0.
    /// \returns A Vec2 object.
    static Vec2 zero()
    {
        static const Vec2 instance(0.0f, 0.0f);
        return instance;
    }

    /// \brief Gets a Vec2 object representing the up direction (0, 1).
    /// \returns A Vec2 object.
    static Vec2 up()
    {
        static const Vec2 instance(0.0f, 1.0f);
        return instance;
    }

    /// \brief Gets a Vec2 object representing the down direction (0, -1).
    /// \returns A Vec2 object.
    static Vec2 down()
    {
        static const Vec2 instance(0.0f, -1.0f);
        return instance;
    }

    /// \brief Gets a Vec2 object representing the right direction (1, 0).
    /// \returns A Vec2 object.
    static Vec2 right()
    {
        static const Vec2 instance(1.0f, 0.0f);
        return instance;
    }

    /// \brief Gets a Vec2 object representing the left direction (-1, 0).
    /// \returns A Vec2 object.
    static Vec2 left()
    {
        static const Vec2 instance(-1.0f, 0.0f);
        return instance;
    }

    /// \brief Gets a unit Vec2 object (normalized version of Vec2::one()).
    /// \return A Vec2 object.
    static Vec2 unit()
    {
        static const Vec2 instance = Vec2::one().Normalize();
        return instance;
    }

    /// \brief Gets the unit vector along the x-axis (right).
    /// \return The unit vector [1, 0].
    inline static Vec2 i() { return right(); }

    /// \brief Gets the unit vector along the y-axis (up).
    /// \return The unit vector [0, 1].
    inline static Vec2 j() { return up(); }

    /// \brief Outputs a Vec2 object to an output stream in a formatted manner.
    /// \param[in] os The output stream to write to.
    /// \param[in] vec The Vec2 object to output.
    /// \return The same output stream, for chaining.
    friend std::ostream& operator<<(std::ostream& os, const Vec2& vec)
    {
        os << '(' << vec.x << ", " << vec.y << ')';
        return os;
    }
};

/// \brief Multiplies a scalar value by the specified Vec2.
/// \param[in] scalar The scalar value.
/// \param[in] vec The Vec2.
/// \return The product of the scalar value and the Vec2.
inline Vec2 operator*(float scalar, const Vec2& vec)
{
    return vec * scalar;
}

/// \brief Divides a scalar value by the specified Vec2.
/// \param[in] scalar The scalar value.
/// \param[in] vec The Vec2.
/// \return The quotient of the scalar value and the Vec2, computed per-component.
inline Vec2 operator/(float scalar, const Vec2& vec)
{
    return vec / scalar;
}

} // namespace HarvestHavoc::Math
