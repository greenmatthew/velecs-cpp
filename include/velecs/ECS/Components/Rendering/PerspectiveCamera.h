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

#include "velecs/Math/Consts.h"

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

    const float& GetNearPlaneOffset() const
    {
        return nearPlaneOffset;
    }

    const float& GetFarPlaneOffset() const
    {
        return farPlaneOffset;
    }

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
        // Define the coordinate system change matrix (X)
        glm::mat4 X = glm::mat4(1.0f); // Start with an identity matrix
        X[1][1] = -1.0f; // Flip Y axis
        X[2][2] = -1.0f; // Flip Z axis

        const float vFovRads = DEG_TO_RAD * verticalFov;
        const float focalLength = 1.0 / (std::tan(vFovRads * 0.5));
        const float x = focalLength / aspectRatio;
        const float y = focalLength;
        const float A = farPlaneOffset / (farPlaneOffset - nearPlaneOffset);
        const float B = -nearPlaneOffset * A;

        // Define the right-handed perspective projection matrix manually
        glm::mat4 perspectiveMatrix = glm::mat4(0.0f); // Initialize all elements to 0
        perspectiveMatrix[0][0] = x;
        perspectiveMatrix[1][1] = y; // Negative for Vulkan's Y-axis
        perspectiveMatrix[2][2] = A;
        perspectiveMatrix[2][3] = 1.0f; // For perspective projection
        perspectiveMatrix[3][2] = B;

        // Combine the projection matrix with the coordinate system change matrix
        // This is because Vulkan switches coordinate systems between world space and NDC space.
        // Pre-applying this change to the perspective matrix so it is not forgotten.
        projectionMatrix = perspectiveMatrix * X;
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
