/// @file    PerspectiveCamera.h
/// @author  Matthew Green
/// @date    11/01/2023 19:49:11
/// 
/// @section LICENSE
/// 
/// Copyright (c) 2023 Matthew Green - All rights reserved
/// Unauthorized copying of this file, via any medium is strictly prohibited
/// Proprietary and confidential

#pragma once

#include "velecs/ECS/Components/Rendering/Camera.h"

#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace velecs {

/// @struct PerspectiveCamera
/// @brief Represents a perspective camera.
///
/// The PerspectiveCamera struct encapsulates the properties of a perspective camera,
/// including its vertical field of view, aspect ratio, and clipping planes. 
/// The vertical field of view and aspect ratio define the camera's frustum, 
/// while the near and far plane offsets define the range along the Z-axis 
/// where objects are rendered.
struct PerspectiveCamera : public Camera {
    // Enums

    // Public Fields

    // Constructors and Destructors

    /// @brief Constructor.
    /// @param[in] extent The visible area of the camera.
    /// @param[in] verticalFov The vertical field of view of the camera.
    /// @param[in] nearPlaneOffset The offset of the near clipping plane.
    /// @param[in] farPlaneOffset The offset of the far clipping plane.
    PerspectiveCamera(const Vec2 resolution = Vec2{1920.0f, 1080.0f},
        const float verticalFov = 70.0f,
        const float nearPlaneOffset = 0.1f,
        const float farPlaneOffset = 200.0f)
        : Camera(resolution, nearPlaneOffset, farPlaneOffset),
            verticalFov(verticalFov)
        {
            RecalculateProjectionMatrix();
        }
    
    PerspectiveCamera(PerspectiveCamera&&) = default;

    /// @brief Default deconstructor.
    ~PerspectiveCamera() override = default;

    // Public Methods

    PerspectiveCamera& operator=(PerspectiveCamera&&) = default;
    
    const float& SetVerticalFov(const float verticalFov)
    {
        this->verticalFov = verticalFov;
        RecalculateProjectionMatrix();
    }

    const float& GetVerticalFov() const
    {
        return verticalFov;
    }

    const glm::mat4 GetProjectionMatrix() const override
    {
        return glm::perspective
        (
            glm::radians(GetVerticalFov()),
            GetAspectRatio(),
            nearPlaneOffset,
            farPlaneOffset
        );
    }

    const glm::mat4& GetProjectionMatrix2() const
    {
        return projectionMatrix;
    }

    void RecalculateProjectionMatrix()
    {
        projectionMatrix = glm::perspective
        (
            glm::radians(GetVerticalFov()),
            GetAspectRatio(),
            nearPlaneOffset,
            farPlaneOffset
        );
    }

protected:
    // Protected Fields

    float verticalFov; /// @brief The vertical field of view of the camera in degrees.

    // Protected Methods

private:
    // Private Fields

    glm::mat4 projectionMatrix = glm::mat4(1.0f);

    // Private Methods
};

} // namespace velecs
