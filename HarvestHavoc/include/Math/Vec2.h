#pragma once

#include "Math/Consts.h"

#include <string>
#include <ostream>
#include <cmath>

namespace HarvestHavoc::Math {
/// <summary>
/// A 2D vector structure for representing points or vectors in 2D space.
/// </summary>
struct Vec2
{
public:
    float x;  ///< The x-coordinate.
    float y;  ///< The y-coordinate.

    /*
    * Basic Operations:
    * 
    * [*] Negation (-vec)
    * [*] Assignment (a = b)
    * [*] Copy Assignment (typically handled by a copy constructor and assignment operator in C++)
    * 
    * Arithmetic Operations:
    * 
    * [*] Addition (a + b)
    * [*] Subtraction (a - b)
    * [*] Scalar Multiplication (vec * scalar)
    * [*] Scalar Division (vec / scalar)
    * 
    * Vector Operations:
    * 
    * [*] Normalization (reducing the vector to unit length)
    * [*] Dot Product (the sum of the product of corresponding elements)
    * [*] Cross Product (a vector perpendicular to the plane of the two input vectors - note that in 2D, this results in a scalar value)
    * [*] Hadamard (or element-wise) Product (the product of corresponding elements)
    * 
    * Utility Methods:
    * 
    * [*] Norms (L0, L1, L2, etc.)
    * [*] Static getters for commonly used vectors (e.g., unit vectors along the axes)
    * 
    * Comparison Operations:
    * 
    * [*] Equality and Inequality (a == b, a != b)
    * 
    * Miscellaneous:
    * 
    * [*] Overloaded output operator for easy logging and debugging (std::cout << vec)
    * [*] Maybe some method to convert the vector to a string for further manipulation or display.
    * [*] A method to compute the angle between two vectors could be useful.
    */

    /// <summary>
    /// Constructs a Vec2 with the specified coordinates.
    /// </summary>
    /// <param name="x">The x-coordinate.</param>
    /// <param name="y">The y-coordinate.</param>
    Vec2(const float x, const float y);

    /// <summary>
    /// Copy constructor. Constructs a new Vec2 with the same values as the specified Vec2.
    /// </summary>
    /// <param name="other">The Vec2 to copy.</param>
    Vec2(const Vec2& other);

    /// <summary>
    /// Destructor. Destroys the Vec2 object.
    /// </summary>
    ~Vec2();

    /// <summary>
    /// Assigns the values of another Vec2 object to this Vec2 object.
    /// </summary>
    /// <param name="other">The other Vec2 object whose values will be assigned to this Vec2 object.</param>
    /// <returns>A reference to this Vec2 object, after the assignment.</returns>
    Vec2& operator=(const Vec2& other);

    /// <summary>
    /// Checks if this Vec2 is equal to the specified Vec2.
    /// </summary>
    /// <param name="other">The Vec2 to compare with.</param>
    /// <returns>True if the Vec2s are equal, false otherwise.</returns>
    bool operator==(const Vec2& other) const;

    /// <summary>
    /// Checks if this Vec2 is not equal to the specified Vec2.
    /// </summary>
    /// <param name="other">The Vec2 to compare with.</param>
    /// <returns>True if the Vec2s are not equal, false otherwise.</returns>
    bool operator!=(const Vec2& other) const;

    /// <summary>
    /// Negates this Vec2 object, producing a new Vec2 object with the negated values.
    /// </summary>
    /// <returns>A new Vec2 object with the negated values of this Vec2 object.</returns>
    Vec2 operator-() const;

    /// <summary>
    /// Adds another Vec2 to this Vec2.
    /// </summary>
    /// <param name="other">The other Vec2.</param>
    /// <returns>A new Vec2 that is the sum of this Vec2 and the other Vec2.</returns>
    Vec2 operator+(const Vec2& other) const;

    /// <summary>
    /// Subtracts another Vec2 from this Vec2.
    /// </summary>
    /// <param name="other">The other Vec2.</param>
    /// <returns>A new Vec2 that is the difference of this Vec2 and the other Vec2.</returns>
    Vec2 operator-(const Vec2& other) const;

    /// <summary>
    /// Multiplies this Vec2 by a scalar.
    /// </summary>
    /// <param name="scalar">The scalar value.</param>
    /// <returns>A new Vec2 that is the product of this Vec2 and the scalar.</returns>
    Vec2 operator*(const float scalar) const;

    friend Vec2 operator*(float scalar, const Vec2& vec);

    /// <summary>
    /// Divides this Vec2 by a scalar.
    /// </summary>
    /// <param name="scalar">The scalar value.</param>
    /// <returns>A new Vec2 that is the quotient of this Vec2 and the scalar.</returns>
    Vec2 operator/(const float scalar) const;

    friend Vec2 operator/(float scalar, const Vec2& vec);

    /// <summary>
    /// Adds another Vec2 to this Vec2 and assigns the result to this Vec2.
    /// </summary>
    /// <param name="other">The other Vec2.</param>
    /// <returns>A reference to this Vec2.</returns>
    Vec2& operator+=(const Vec2& other);

    /// <summary>
    /// Subtracts another Vec2 from this Vec2 and assigns the result to this Vec2.
    /// </summary>
    /// <param name="other">The other Vec2.</param>
    /// <returns>A reference to this Vec2.</returns>
    Vec2& operator-=(const Vec2& other);

    /// <summary>
    /// Multiplies this Vec2 by a scalar and assigns the result to this Vec2.
    /// </summary>
    /// <param name="scalar">The scalar value.</param>
    /// <returns>A reference to this Vec2.</returns>
    Vec2& operator*=(const float scalar);

    /// <summary>
    /// Divides this Vec2 by a scalar and assigns the result to this Vec2.
    /// </summary>
    /// <param name="scalar">The scalar value.</param>
    /// <returns>A reference to this Vec2.</returns>
    Vec2& operator/=(const float scalar);

    /// <summary>
    /// Computes the L0 norm of this Vec2, which is the count of non-zero components.
    /// </summary>
    /// <returns>The L0 norm.</returns>
    unsigned int L0Norm() const;

    /// <summary>
    /// Computes the L1 norm of this Vec2, which is the sum of the absolute values of the components.
    /// </summary>
    /// <returns>The L1 norm.</returns>
    float L1Norm() const;

    /// <summary>
    /// Computes the L2 norm (magnitude) of this Vec2.
    /// </summary>
    /// <returns>The L2 norm.</returns>
    float L2Norm() const;

    /// <summary>
    /// Alias for L2Norm, computes the L2 norm (magnitude) of this Vec2.
    /// </summary>
    /// <returns>The L2 norm.</returns>
    inline float Norm() const { return L2Norm(); }

    /// <summary>
    /// Alias for L2Norm, computes the L2 norm (magnitude) of this Vec2.
    /// </summary>
    /// <returns>The L2 norm.</returns>
    inline float Magnitude() const { return L2Norm(); }

    /// <summary>
    /// Normalizes this Vec2, making its magnitude equal to 1.
    /// </summary>
    /// <returns>The normalized Vec2.</returns>
    Vec2 Normalize() const;

    /// <summary>
    /// Projects the vector onto the i basis vector (x-axis).
    /// </summary>
    /// <returns>The projection of the vector onto the i basis vector.</returns>
    Vec2 ProjOntoI() const;

    /// <summary>
    /// Projects the vector onto the j basis vector (y-axis).
    /// </summary>
    /// <returns>The projection of the vector onto the j basis vector.</returns>
    Vec2 ProjOntoJ() const;

    /// <summary>
    /// Computes the dot product of two Vec2 objects.
    /// </summary>
    /// <param name="a">The first Vec2 object.</param>
    /// <param name="b">The second Vec2 object.</param>
    /// <returns>The dot product of a and b.</returns>
    static float Dot(const Vec2& a, const Vec2& b);

    /// <summary>
    /// Computes the cross product of two Vec2 objects.
    /// </summary>
    /// <param name="a">The first Vec2 object.</param>
    /// <param name="b">The second Vec2 object.</param>
    /// <returns>The cross product of a and b.</returns>
    static float Cross(const Vec2& a, const Vec2& b);

    /// <summary>
    /// Computes the Hadamard product of two Vec2 objects.
    /// </summary>
    /// <param name="a">The first Vec2 object.</param>
    /// <param name="b">The second Vec2 object.</param>
    /// <returns>The Hadamard product of a and b.</returns>
    static Vec2 Hadamard(const Vec2& a, const Vec2& b);

    /// <summary>
    /// Alias for Hadamard, computes the element-wise multiplication of two Vec2s.
    /// </summary>
    /// <param name="a">The first Vec2.</param>
    /// <param name="b">The second Vec2.</param>
    /// <returns>The element-wise multiplication of the two Vec2s.</returns>
    inline static Vec2 ElementwiseMultiply(const Vec2& a, const Vec2& b) { return Hadamard(a, b); }

    /// <summary>
    /// Clamps the components of a Vec2 between the corresponding components of two other Vec2s.
    /// </summary>
    /// <param name="vec">The Vec2 to clamp.</param>
    /// <param name="min">The Vec2 representing the minimum values.</param>
    /// <param name="max">The Vec2 representing the maximum values.</param>
    /// <returns>The clamped Vec2.</returns>
    static Vec2 Clamp(const Vec2& vec, const Vec2& min, const Vec2& max);

    /// <summary>
    /// Computes a linear interpolation between two Vec2s.
    /// </summary>
    /// <param name="vec1">The first Vec2.</param>
    /// <param name="vec2">The second Vec2.</param>
    /// <param name="t">The interpolation factor. A value of 0 returns vec1, and a value of 1 returns vec2.</param>
    /// <returns>The interpolated Vec2.</returns>
    static Vec2 Lerp(const Vec2& vec1, const Vec2& vec2, float t);

    /// <summary>
    /// Computes the angle between two vectors in radians.
    /// </summary>
    /// <param name="a">The first vector.</param>
    /// <param name="b">The second vector.</param>
    /// <returns>The angle between the vectors in radians.</returns>
    static float Angle(const Vec2& a, const Vec2& b)
    {
        float dotProduct = Dot(a, b);
        float magnitudes = a.L2Norm() * b.L2Norm();
        if (magnitudes == 0) return 0;  // avoid division by zero
        float cosineTheta = dotProduct / magnitudes;
        return std::acos(cosineTheta);  // result is in radians
    }

    /// <summary>
    /// Computes the angle between two vectors in degrees.
    /// </summary>
    /// <param name="a">The first vector.</param>
    /// <param name="b">The second vector.</param>
    /// <returns>The angle between the vectors in degrees.</returns>
    static float AngleDeg(const Vec2& a, const Vec2& b)
    {
        return Angle(a, b) * (180.0f / PI);  // convert radians to degrees
    }


    /// <summary>
    /// Converts the Vec2 to a string representation.
    /// </summary>
    /// <returns>A string representation of the Vec2.</returns>
    std::string ToString() const;

    /// <summary>
    /// Gets a Vec2 object with both coordinates set to 1.
    /// </summary>
    /// <returns>A Vec2 object.</returns>
    static Vec2 one()
    {
        static const Vec2 instance(1.0f, 1.0f);
        return instance;
    }

    /// <summary>
    /// Gets a Vec2 object with both coordinates set to 0.
    /// </summary>
    /// <returns>A Vec2 object.</returns>
    static Vec2 zero()
    {
        static const Vec2 instance(0.0f, 0.0f);
        return instance;
    }

    /// <summary>
    /// Gets a Vec2 object representing the up direction (0, 1).
    /// </summary>
    /// <returns>A Vec2 object.</returns>
    static Vec2 up()
    {
        static const Vec2 instance(0.0f, 1.0f);
        return instance;
    }

    /// <summary>
    /// Gets a Vec2 object representing the down direction (0, -1).
    /// </summary>
    /// <returns>A Vec2 object.</returns>
    static Vec2 down()
    {
        static const Vec2 instance(0.0f, -1.0f);
        return instance;
    }

    /// <summary>
    /// Gets a Vec2 object representing the right direction (1, 0).
    /// </summary>
    /// <returns>A Vec2 object.</returns>
    static Vec2 right()
    {
        static const Vec2 instance(1.0f, 0.0f);
        return instance;
    }

    /// <summary>
    /// Gets a Vec2 object representing the left direction (-1, 0).
    /// </summary>
    /// <returns>A Vec2 object.</returns>
    static Vec2 left()
    {
        static const Vec2 instance(-1.0f, 0.0f);
        return instance;
    }

    /// <summary>
    /// Gets a unit Vec2 object (normalized version of Vec2::one()).
    /// </summary>
    /// <returns>A Vec2 object.</returns>
    static Vec2 unit()
    {
        static const Vec2 instance = Vec2::one().Normalize();
        return instance;
    }

    /// <summary>
    /// Gets the unit vector along the x-axis (right).
    /// </summary>
    /// <returns>The unit vector [1, 0].</returns>
    inline static Vec2 i() { return right(); }

    /// <summary>
    /// Gets the unit vector along the y-axis (up).
    /// </summary>
    /// <returns>The unit vector [0, 1].</returns>
    inline static Vec2 j() { return up(); }

    /// <summary>
    /// Outputs a Vec2 object to an output stream in a formatted manner.
    /// </summary>
    /// <param name="os">The output stream to write to.</param>
    /// <param name="vec">The Vec2 object to output.</param>
    /// <returns>The same output stream, for chaining.</returns>
    friend std::ostream& operator<<(std::ostream& os, const Vec2& vec)
    {
        os << '(' << vec.x << ", " << vec.y << ')';
        return os;
    }
};

/// <summary>
/// Multiplies a scalar value by the specified Vec2.
/// </summary>
/// <param name="scalar">The scalar value.</param>
/// <param name="vec">The Vec2.</param>
/// <returns>The product of the scalar value and the Vec2.</returns>
inline Vec2 operator*(float scalar, const Vec2& vec)
{
    return vec * scalar;  // Assumes you've defined Vec2::operator*(float)
}

/// <summary>
/// Divides a scalar value by the specified Vec2.
/// </summary>
/// <param name="scalar">The scalar value.</param>
/// <param name="vec">The Vec2.</param>
/// <returns>The quotient of the scalar value and the Vec2, computed per-component.</returns>
inline Vec2 operator/(float scalar, const Vec2& vec)
{
    return vec / scalar;
}

} // namespace HarvestHavoc::Math
