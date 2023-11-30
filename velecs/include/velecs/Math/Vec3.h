/// @file    Vec3.h
/// @author  Matthew Green
/// @date    10/27/2023 17:22:56
/// 
/// @section LICENSE
/// 
/// Copyright (c) 2023 Matthew Green - All rights reserved
/// Unauthorized copying of this file, via any medium is strictly prohibited
/// Proprietary and confidential

#pragma once

#include "velecs/Math/Consts.h"

#include <glm/vec3.hpp>

#include <iostream>

namespace velecs {

struct Vec2;

/// @struct Vec3
/// @brief Brief description.
///
/// Rest of description.
struct Vec3 {
public:
    // Enums

    // Public Fields

    static const Vec3 ZERO;         /// @brief A vector with all components set to zero (0, 0, 0).
    static const Vec3 ONE;          /// @brief A vector with all components set to one (1, 1, 1).
    static const Vec3 NEG_ONE;      /// @brief A vector with all components set to negative one (-1, -1, -1).
    static const Vec3 UP;           /// @brief A vector representing the up direction in a right-handed coordinate system (0, -1, 0).
    static const Vec3 DOWN;         /// @brief A vector representing the down direction in a right-handed coordinate system (0, 1, 0).
    static const Vec3 RIGHT;        /// @brief A vector representing the right direction in a right-handed coordinate system (1, 0, 0).
    static const Vec3 LEFT;         /// @brief A vector representing the left direction in a right-handed coordinate system (-1, 0, 0).
    static const Vec3 FORWARD;      /// @brief A vector representing the forward direction in a right-handed coordinate system (0, 0, 1).
    static const Vec3 BACKWARD;     /// @brief A vector representing the backward direction in a right-handed coordinate system (0, 0, -1).
    static const Vec3 POS_INFINITY; /// @brief A vector with all components set to positive infinity.
    static const Vec3 NEG_INFINITY; /// @brief A vector with all components set to negative infinity.
    static const Vec3 UNIT;         /// @brief A normalized vector with magnitude equal to 1. Derived from Vec3::ONE.
    static const Vec3 I;            /// @brief A unit vector along the x-axis (1, 0, 0).
    static const Vec3 J;            /// @brief A unit vector along the y-axis (0, 1, 0).
    static const Vec3 K;            /// @brief A unit vector along the z-axis (0, 0, 1).
    

    float x; /// @brief The x-component of the vector.
    float y; /// @brief The y-component of the vector.
    float z; /// @brief The z-component of the vector.

    // Constructors and Destructors
    
    /// @brief Constructs a Vec3 with specified x, y, and z components.
    /// @param[in] x The x-component.
    /// @param[in] y The y-component.
    /// @param[in] z The z-component.
    Vec3(const float x, const float y, const float z);

    /// @brief Constructs a Vec3 from a Vec2.
    /// @details The x and y components are initialized from the Vec2, while the z-component is set to 0.0f.
    /// @param[in] vec2 The Vec2 from which to initialize the x and y components.
    Vec3(const Vec2 vec2);

    /// @brief Constructs a Vec3 from a Vec2 and a specified z-component.
    /// @details The x and y components are initialized from the Vec2, while the z-component is set to the specified value.
    /// @param[in] vec2 The Vec2 from which to initialize the x and y components.
    /// @param[in] z The z-component.
    Vec3(const Vec2 vec2, const float z);

    /// @brief Constructs a Vec3 with a specified x-component and a Vec2 for the y and z components.
    /// @details The x-component is set to the specified value, while the y and z components are initialized from the Vec2.
    /// @param[in] x The x-component.
    /// @param[in] vec2 The Vec2 from which to initialize the y and z components.
    Vec3(const float x, const Vec2 vec2);
    
    /// @brief Default destructor.
    ~Vec3() = default;

    // Public Methods

    /// @brief Converts the Vec3 to a glm::vec3.
    /// @returns A glm::vec3 with the same components as this Vec3.
    operator glm::vec3() const;

    /// @brief Assigns the values of another Vec3 object to this Vec3 object.
    /// @param[in] other The other Vec3 object whose values will be assigned to this Vec3 object.
    /// @return A reference to this Vec3 object, after the assignment.
    Vec3& operator=(const Vec3 other);

    /// @brief Checks if this Vec3 is equal to the specified Vec3.
    /// @param[in] other The Vec3 to compare with.
    /// @return True if the Vec3s are equal, false otherwise.
    bool operator==(const Vec3 other) const;

    /// @brief Checks if this Vec3 is not equal to the specified Vec3.
    /// @param[in] other The Vec3 to compare with.
    /// @return True if the Vec3s are not equal, false otherwise.
    bool operator!=(const Vec3 other) const;

    /// @brief Negates this Vec3.
    /// @return A new Vec3 that is the negation of this Vec3.
    Vec3 operator-() const;

    /// @brief Overloads the addition assignment operator to add another Vec3 to this Vec3 and assign the result to this Vec3.
    /// @details This method adds the corresponding components of the other Vec3 to this Vec3 and assigns the result to this Vec3.
    /// @param[in] other The other Vec3 to add to this Vec3.
    /// @returns A reference to this Vec3 after the addition
    Vec3& operator+=(const Vec3 other);

    /// @brief Overloads the subtraction assignment operator to subtract another Vec3 from this Vec3 and assign the result to this Vec3.
    /// @details This method subtracts the corresponding components of the other Vec3 from this Vec3 and assigns the result to this Vec3.
    /// @param[in] other The other Vec3 to subtract from this Vec3.
    /// @returns A reference to this Vec3 after the subtraction.
    Vec3& operator-=(const Vec3 other);

    /// @brief Overloads the multiplication assignment operator to multiply this Vec3 by a scalar and assign the result to this Vec3.
    /// @details This method multiplies the components of this Vec3 by the specified scalar value and assigns the result to this Vec3.
    /// @param[in] scalar The scalar value to multiply this Vec3 by.
    /// @returns A reference to this Vec3 after the multiplication.
    Vec3& operator*=(const float scalar);

    /// @brief Overloads the division assignment operator to divide this Vec3 by a scalar and assign the result to this Vec3.
    /// @details This method divides the components of this Vec3 by the specified scalar value and assigns the result to this Vec3.
    /// @param[in] scalar The scalar value to divide this Vec3 by.
    /// @returns A reference to this Vec3 after the division.
    Vec3& operator/=(const float scalar);

    /// @brief Computes the L0 norm of this Vec3, which is the count of non-zero components.
    /// @returns The L0 norm.
    unsigned int L0Norm() const;

    /// @brief Computes the L1 norm of this Vec3, which is the sum of the absolute values of the components.
    /// @returns The L1 norm.
    float L1Norm() const;

    /// @brief Computes the L2 norm (magnitude) of this Vec3.
    /// @returns The L2 norm.
    float L2Norm() const;

    /// @brief Alias for L2Norm, computes the L2 norm (magnitude) of this Vec3.
    /// @returns The L2 norm.
    inline float Norm() const { return L2Norm(); }

    /// @brief Alias for L2Norm, computes the L2 norm (magnitude) of this Vec3.
    /// @returns The L2 norm.
    inline float Magnitude() const { return L2Norm(); }

    /// @brief Normalizes this Vec3, making its magnitude equal to 1.
    /// @returns The normalized Vec3.
    /// @note If the original magnitude is 0, returns the zero vector.
    Vec3 Normalize() const;

    /// @brief Projects the vector onto the i basis vector (x-axis).
    /// @returns The projection of the vector onto the i basis vector,
    /// resulting in a vector along the x-axis with the same x component as the original vector.
    Vec3 ProjOntoI() const;

    /// @brief Projects the vector onto the j basis vector (y-axis).
    /// @returns The projection of the vector onto the j basis vector,
    /// resulting in a vector along the y-axis with the same y component as the original vector.
    Vec3 ProjOntoJ() const;

    /// @brief Projects the vector onto the k basis vector (z-axis).
    /// @returns The projection of the vector onto the k basis vector,
    /// resulting in a vector along the z-axis with the same z component as the original vector.
    Vec3 ProjOntoK() const;

    /// @brief Computes the dot product of two Vec3 objects.
    /// @param a The first Vec3 object.
    /// @param b The second Vec3 object.
    /// @returns The dot product of a and b.
    static float Dot(const Vec3 a, const Vec3 b);

    /// @brief Computes the cross product of two Vec3 objects.
    /// @param a The first Vec3 object.
    /// @param b The second Vec3 object.
    /// @returns The cross product of a and b.
    static Vec3 Cross(const Vec3 a, const Vec3 b);

    /// @brief Computes the Hadamard product of two Vec3 objects.
    /// @param a The first Vec3 object.
    /// @param b The second Vec3 object.
    /// @returns The Hadamard product of a and b.
    static Vec3 Hadamard(const Vec3 a, const Vec3 b);

    /// @brief Alias for Hadamard, computes the element-wise multiplication of two Vec3s.
    /// @param a The first Vec3.
    /// @param b The second Vec3.
    /// @returns The element-wise multiplication of the two Vec3s.
    inline static Vec3 ElementwiseMultiply(const Vec3 a, const Vec3 b) { return Hadamard(a, b); }

    /// @brief Clamps the components of a Vec3 between the corresponding components of two other Vec3s.
    /// @param vec The Vec3 to clamp.
    /// @param min The Vec3 representing the minimum values.
    /// @param max The Vec3 representing the maximum values.
    /// @returns The clamped Vec3.
    static Vec3 Clamp(const Vec3 vec, const Vec3 min, const Vec3 max);

    /// @brief Computes a linear interpolation between two Vec3s.
    /// @param a The first Vec3.
    /// @param b The second Vec3.
    /// @param t The interpolation factor. A value of 0 returns a, and a value of 1 returns b.
    /// @returns The interpolated Vec3.
    static Vec3 Lerp(const Vec3 a, const Vec3 b, float t);

    /// @brief Computes the angle between two vectors in radians.
    /// @param a The first vector.
    /// @param b The second vector.
    /// @returns The angle between the vectors in radians.
    static float Angle(const Vec3 a, const Vec3 b);

    /// @brief Computes the angle between two vectors in degrees.
    /// @param a The first vector.
    /// @param b The second vector.
    /// @returns The angle between the vectors in degrees.
    inline static float AngleDeg(const Vec3 a, const Vec3 b)
    {
        return Angle(a, b) * (180.0f / PI);  // convert radians to degrees
    }

    /// @brief Converts the Vec3 to a string representation.
    /// @returns A string representation of the Vec3.
    std::string ToString() const;

    /// @brief Outputs a Vec3 object to an output stream in a formatted manner.
    /// @param[in] os The output stream to write to.
    /// @param[in] vec The Vec3 object to output.
    /// @return The same output stream, for chaining.
    inline friend std::ostream& operator<<(std::ostream& os, const Vec3 vec)
    {
        os << vec.ToString();
        return os;
    }

protected:
    // Protected Fields

    // Protected Methods

private:
    // Private Fields

    // Private Methods
};

/// @brief Overloads the addition operator to add two Vec3 objects together.
/// @details This method adds the corresponding components of the two Vec3 objects together.
/// @param[in] lhs The left-hand side Vec3 operand.
/// @param[in] rhs The right-hand side Vec3 operand.
/// @returns A new Vec3 object representing the sum of the two Vec3 operands.
Vec3 operator+(const Vec3 lhs, const Vec3 rhs);

/// @brief Overloads the subtraction operator to subtract one Vec3 from another.
/// @details This method subtracts the corresponding components of the two Vec3 objects.
/// @param[in] lhs The left-hand side Vec3 operand.
/// @param[in] rhs The right-hand side Vec3 operand.
/// @returns A new Vec3 object representing the difference of the two Vec3 operands.
Vec3 operator-(const Vec3 lhs, const Vec3 rhs);

/// @brief Overloads the multiplication operator to multiply a Vec3 object by a scalar value.
/// @details This method multiplies each component of the Vec3 object by the scalar value.
/// @param[in] lhs The Vec3 object to be multiplied.
/// @param[in] rhs The scalar value by which to multiply the Vec3 object.
/// @returns A new Vec3 object representing the product of the Vec3 object and the scalar value.
Vec3 operator*(const Vec3 lhs, const float rhs);

/// @brief Overloads the division operator to divide a Vec3 by a scalar.
/// @details This method divides the components of the Vec3 by the specified scalar value.
/// @param[in] lhs The Vec3 operand.
/// @param[in] rhs The scalar operand.
/// @returns A new Vec3 object representing the quotient of the Vec3 and scalar operands.
Vec3 operator/(const Vec3 lhs, const float rhs);

/// @brief Overloads the multiplication operator to multiply a scalar value by a Vec3 object.
/// @details This method multiplies each component of the Vec3 object by the scalar value. 
/// This overload ensures that multiplication is commutative.
/// @param[in] lhs The scalar value by which to multiply the Vec3 object.
/// @param[in] rhs The Vec3 object to be multiplied.
/// @returns A new Vec3 object representing the product of the scalar value and the Vec3 object.
inline Vec3 operator*(const float lhs, const Vec3 rhs)
{
    return rhs * lhs;
}

} // namespace velecs
