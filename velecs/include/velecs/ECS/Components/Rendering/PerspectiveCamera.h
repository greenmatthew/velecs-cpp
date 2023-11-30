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
struct PerspectiveCamera {
    // Enums

    // Public Fields

    // Constructors and Destructors

    /// @brief Constructor.
    /// @param[in] extent The visible area of the camera.
    /// @param[in] verticalFov The vertical field of view of the camera.
    /// @param[in] nearPlaneOffset The offset of the near clipping plane.
    /// @param[in] farPlaneOffset The offset of the far clipping plane.
    PerspectiveCamera
    (
        const float aspectRatio = 16.0f / 9.0f,
        const float verticalFov = 70.0f,
        const float nearPlaneOffset = 0.1f,
        const float farPlaneOffset = 200.0f
    )
        : aspectRatio(aspectRatio),
            verticalFov(verticalFov),
            nearPlaneOffset(nearPlaneOffset),
            farPlaneOffset(farPlaneOffset)
    {
        RecalculateProjectionMatrix();
    }
    
    /// @brief Constructor.
    /// @param[in] extent The visible area of the camera.
    /// @param[in] verticalFov The vertical field of view of the camera.
    /// @param[in] nearPlaneOffset The offset of the near clipping plane.
    /// @param[in] farPlaneOffset The offset of the far clipping plane.
    PerspectiveCamera
    (
        const Vec2 resolution,
        const float verticalFov = 70.0f,
        const float nearPlaneOffset = 0.1f,
        const float farPlaneOffset = 200.0f
    )
        : aspectRatio(resolution.x / resolution.y),
            verticalFov(verticalFov),
            nearPlaneOffset(nearPlaneOffset),
            farPlaneOffset(farPlaneOffset)
    {
        RecalculateProjectionMatrix();
    }
    
    /// @brief Default deconstructor.
    ~PerspectiveCamera() = default;

    // Public Methods

    const float& GetAspectRatio() const
    {
        return aspectRatio;
    }

    void SetAspectRatio(const float aspectRatio)
    {
        this->aspectRatio = aspectRatio;
        RecalculateProjectionMatrix();
    }

    const float& SetVerticalFov(const float verticalFov)
    {
        this->verticalFov = verticalFov;
        RecalculateProjectionMatrix();
    }

    const float& GetVerticalFov() const
    {
        return verticalFov;
    }

    const glm::mat4& GetProjectionMatrix() const
    {
        return projectionMatrix;
    }

    void RecalculateProjectionMatrix()
    {
        projectionMatrix = glm::perspective
        (
            glm::radians(verticalFov),
            aspectRatio,
            nearPlaneOffset,
            farPlaneOffset
        );
    }

protected:
    // Protected Fields

    // Protected Methods

private:
    // Private Fields

    float aspectRatio; /// @brief The aspect ratio of the camera (width / height).

    float verticalFov; /// @brief The vertical field of view of the camera in degrees.

    float nearPlaneOffset; /// @brief The offset of the near clipping plane along the Z-axis.
    float farPlaneOffset; /// @brief The offset of the far clipping plane along the Z-axis.

    glm::mat4 projectionMatrix = glm::mat4(1.0f);

    // Private Methods
};

} // namespace velecs
