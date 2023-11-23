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
/// @brief Brief description.
///
/// Rest of description.
struct Transform {    
public:
    // Enums

    // Public Fields

    flecs::entity entity{flecs::entity::null()};
    Vec3 position{Vec3::ZERO};
    Vec3 rotation{Vec3::ZERO};
    Vec3 scale{Vec3::ONE};

    // Constructors and Destructors

    /// @brief Default constructor.
    Transform() = default;

    /// @brief Constructor.
    Transform(flecs::entity entity, Vec3 position = Vec3::ZERO, Vec3 rotation = Vec3::ZERO, Vec3 scale = Vec3::ONE);

    /// @brief Default deconstructor.
    ~Transform() = default;

    // Public Methods

    flecs::entity GetParent() const;

    bool TryGetParent(flecs::entity& parentEntity) const;

    const Transform* const GetParentTransform() const;

    bool TryGetParentTransform(const Transform*& transform) const;

    const Vec3 GetAbsPosition() const;

    flecs::entity GetCameraEntity() const;

    const Camera* const GetCamera() const;

    Camera* const GetCamera();

    const Transform* const GetCameraTransform() const;

    Transform* const GetCameraTransform();



    glm::mat4 GetRenderMatrix() const;

    const Vec2 GetScreenPosition(const Vec3 cameraAbsPos) const;

protected:
    // Protected Fields

    // Protected Methods

private:
    // Private Fields

    // Private Methods

    static glm::mat4 GetProjectionMatrix(const Camera* const camera);
};

} // namespace velecs
