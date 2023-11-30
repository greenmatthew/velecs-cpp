/// @file    OrthoCamera.h
/// @author  Matthew Green
/// @date    11/01/2023 17:51:07
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

/// @struct OrthoCamera
/// @brief Represents an orthographic camera.
///
/// The OrthoCamera struct encapsulates the properties of an orthographic camera,
/// including its extent and clipping planes. The extent defines the visible area
/// of the camera in the scene, while the near and far plane offsets define the 
/// range along the Z-axis where objects are rendered.
struct OrthoCamera {
    // Enums

    // Public Fields

    // Constructors and Destructors

    /// @brief Constructor.
    /// @param[in] extent The visible area of the camera.
    /// @param[in] nearPlaneOffset The offset of the near clipping plane.
    /// @param[in] farPlaneOffset The offset of the far clipping plane.
    OrthoCamera(const Rect extent,
                const float nearPlaneOffset = 0.1f,
                const float farPlaneOffset = 200.0f)
        : extent(extent), nearPlaneOffset(nearPlaneOffset), farPlaneOffset(farPlaneOffset) {}

    /// @brief Default deconstructor.
    ~OrthoCamera() = default;

    // Public Methods

    void RecalculateProjectionMatrix()
    {
        throw std::exception("Method is not implemented yet.");

        projectionMatrix = glm::ortho
        (
            extent.min.x,
            extent.min.y,
            extent.max.x,
            extent.max.y,
            nearPlaneOffset,
            farPlaneOffset
        );
    }

    const glm::mat4& GetProjectionMatrix() const
    {
        return projectionMatrix;
    }

protected:
    // Protected Fields

    // Protected Methods

private:
    // Private Fields

    Rect extent;

    float nearPlaneOffset; /// @brief The offset of the near clipping plane along the Z-axis.
    float farPlaneOffset; /// @brief The offset of the far clipping plane along the Z-axis.

    glm::mat4 projectionMatrix = glm::mat4(1.0f);

    // Private Methods
};

} // namespace velecs
