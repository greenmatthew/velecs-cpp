/// \file    Vec3.h
/// \author  Matthew Green
/// \date    10/27/2023 17:22:56
/// 
/// \section LICENSE
/// 
/// Copyright (c) 2023 Matthew Green - All rights reserved
/// Unauthorized copying of this file, via any medium is strictly prohibited
/// Proprietary and confidential

#pragma once

#include <glm/vec3.hpp>

namespace engine {

/// \class Vec3
/// \brief Brief description.
///
/// Rest of description.
struct Vec3 {
public:
    // Enums

    // Public Fields

    static const Vec3 ZERO;    /// \brief A vector with all components set to zero (0, 0, 0).
    static const Vec3 ONE;     /// \brief A vector with all components set to one (1, 1, 1).
    static const Vec3 NEG_ONE; /// \brief A vector with all components set to negative one (-1, -1, -1).
    static const Vec3 UP;      /// \brief A vector representing the up direction in a right-handed coordinate system (0, 1, 0).
    static const Vec3 DOWN;    /// \brief A vector representing the down direction in a right-handed coordinate system (0, -1, 0).
    static const Vec3 RIGHT;   /// \brief A vector representing the right direction in a right-handed coordinate system (1, 0, 0).
    static const Vec3 LEFT;    /// \brief A vector representing the left direction in a right-handed coordinate system (-1, 0, 0).
    static const Vec3 FORWARD; /// \brief A vector representing the forward direction in a right-handed coordinate system (0, 0, -1).
    static const Vec3 BACKWARD;/// \brief A vector representing the backward direction in a right-handed coordinate system (0, 0, 1).
    static const Vec3 POS_INFINITY; /// \brief A vector with all components set to positive infinity.
    static const Vec3 NEG_INFINITY; /// \brief A vector with all components set to negative infinity.
    

    float x; /// \brief The x-component of the vector.
    float y; /// \brief The y-component of the vector.
    float z; /// \brief The z-component of the vector.

    // Constructors and Destructors
    
    /// \brief Constructs a Vec3 with specified x, y, and z components.
    /// \param[in] x The x-component.
    /// \param[in] y The y-component.
    /// \param[in] z The z-component.
    Vec3(const float x, const float y, const float z);

    /// \brief Constructs a Vec3 from a Vec2.
    /// \details The x and y components are initialized from the Vec2, while the z-component is set to 0.0f.
    /// \param[in] vec2 The Vec2 from which to initialize the x and y components.
    Vec3(const struct Vec2 vec2);

    /// \brief Constructs a Vec3 from a Vec2 and a specified z-component.
    /// \details The x and y components are initialized from the Vec2, while the z-component is set to the specified value.
    /// \param[in] vec2 The Vec2 from which to initialize the x and y components.
    /// \param[in] z The z-component.
    Vec3(const struct Vec2 vec2, const float z);

    /// \brief Constructs a Vec3 with a specified x-component and a Vec2 for the y and z components.
    /// \details The x-component is set to the specified value, while the y and z components are initialized from the Vec2.
    /// \param[in] x The x-component.
    /// \param[in] vec2 The Vec2 from which to initialize the y and z components.
    Vec3(const float x, const struct Vec2 vec2);
    
    /// \brief Default destructor.
    ~Vec3() = default;

    // Public Methods

    /// \brief Converts the Vec3 to a glm::vec3.
    /// \returns A glm::vec3 with the same components as this Vec3.
    operator glm::vec3() const;

protected:
    // Protected Fields

    // Protected Methods

private:
    // Private Fields

    // Private Methods
};

} // namespace engine
