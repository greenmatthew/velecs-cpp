/// @file    Transform.h
/// @author  Matthew Green
/// @date    10/30/2023 19:48:02
/// 
/// @section LICENSE
/// 
/// Copyright (c) 2023 Matthew Green - All rights reserved
/// Unauthorized copying of this file, via any medium is strictly prohibited
/// Proprietary and confidential

#pragma once

#include "velecs/Math/Vec3.h"

#include "velecs/ECS/Components/Rendering/MainCamera.h"
#include "velecs/ECS/Components/Rendering/Camera.h"
#include "velecs/ECS/Components/Rendering/OrthoCamera.h"
#include "velecs/ECS/Components/Rendering/PerspectiveCamera.h"

#include <flecs.h>

#include <glm/mat4x4.hpp>

namespace velecs {

/// @struct Transform
/// @brief Represents the position, rotation, and scale of an entity in 3D space.
///
/// The Transform component is used to store and manipulate the position, rotation,
/// and scale of entities in a 3D environment. It provides methods to calculate absolute
/// positions, retrieve associated camera components, and compute transformation matrices
/// for rendering.
struct Transform {    
public:
    // Enums

    // Public Fields

    flecs::entity entity{flecs::entity::null()}; /// @brief The entity this transform component is associated with.
    Vec3 position{Vec3::ZERO}; /// @brief The local position of the entity.
    Vec3 rotation{Vec3::ZERO}; /// @brief The local rotation of the entity in Euler angles (degrees).
    Vec3 scale{Vec3::ONE}; /// @brief The local scale of the entity.

    // Constructors and Destructors

    /// @brief Default constructor.
    Transform() = default;

    /// @brief Constructor to initialize the Transform component with specific values.
    /// @param[in] entity The entity this transform is associated with.
    /// @param[in] position The local position of the entity.
    /// @param[in] rotation The local rotation of the entity in Euler angles.
    /// @param[in] scale The local scale of the entity.
    Transform(flecs::entity entity, Vec3 position = Vec3::ZERO, Vec3 rotation = Vec3::ZERO, Vec3 scale = Vec3::ONE);

    /// @brief Default deconstructor.
    ~Transform() = default;

    // Public Methods

/// @brief Gets the parent entity of this transform's entity.
    /// @throws std::runtime_error if the entity handle is not set.
    /// @return The parent entity.
    flecs::entity GetParent() const;

    /// @brief Attempts to get the parent entity of this transform's entity.
    /// @param[out] parentEntity The parent entity, if found.
    /// @return True if a parent entity exists, false otherwise.
    bool TryGetParent(flecs::entity& parentEntity) const;

    /// @brief Gets the Transform component of the parent entity.
    /// @throws std::runtime_error if the parent entity does not exist.
    /// @return A pointer to the parent's Transform component.
    const Transform* const GetParentTransform() const;

    /// @brief Attempts to get the Transform component of the parent entity.
    /// @param[out] transform The Transform component of the parent entity, if found.
    /// @return True if the parent's Transform component is found, false otherwise.
    bool TryGetParentTransform(const Transform*& transform) const;

    /// @brief Calculates the absolute position of the entity in the world.
    /// @return The absolute world position.
    const Vec3 GetAbsPosition() const;

    /// @brief Retrieves the entity associated with the main camera in the scene.
    /// @throws std::runtime_error if the MainCamera component is missing or uninitialized.
    /// @return The main camera entity.
    flecs::entity GetCameraEntity() const;

    /// @brief Retrieves the Camera component of the main camera entity.
    /// @return A pointer to the Camera component of the main camera entity.
    const Camera* const GetCamera() const;

    /// @brief Retrieves a mutable reference to the Camera component of the main camera entity.
    /// @return A mutable pointer to the Camera component of the main camera entity.
    Camera* const GetCamera();

    /// @brief Retrieves the Transform component of the main camera entity.
    /// @return A pointer to the Transform component of the main camera entity.
    const Transform* const GetCameraTransform() const;

    /// @brief Retrieves a mutable reference to the Transform component of the main camera entity.
    /// @return A mutable pointer to the Transform component of the main camera entity.
    Transform* const GetCameraTransform();

    /// @brief Computes the model matrix based on the entity's position, rotation, and scale.
    /// @param[in] useScale Determines whether to include scaling in the matrix.
    /// @return The computed model matrix.
    glm::mat4 GetModelMatrix(const bool useScale = true) const;

    /// @brief Calculates the render matrix for perspective camera rendering.
    /// @param[in] cameraTransform The Transform component of the camera.
    /// @param[in] perspectiveCamera The PerspectiveCamera component associated with the camera.
    /// @return The render matrix combining the model, view, and projection matrices.
    glm::mat4 GetRenderMatrix(const Transform* const cameraTransform, const PerspectiveCamera* const perspectiveCamera) const;

    /// @brief Calculates the render matrix for orthographic camera rendering.
    /// @param[in] cameraTransform The Transform component of the camera.
    /// @param[in] orthoCamera The OrthoCamera component associated with the camera.
    /// @return The render matrix combining the model, view, and projection matrices.
    glm::mat4 GetRenderMatrix(const Transform* const cameraTransform, const OrthoCamera* const orthoCamera) const;

    const Vec2 GetScreenPosition(const Transform* const cameraTransform, const PerspectiveCamera* const perspectiveCamera) const;

protected:
    // Protected Fields

    // Protected Methods

private:
    // Private Fields

    // Private Methods
};

} // namespace velecs
