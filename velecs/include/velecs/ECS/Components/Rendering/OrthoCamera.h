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

#include "velecs/ECS/Components/Rendering/Camera.h"

namespace velecs {

/// @struct OrthoCamera
/// @brief Represents an orthographic camera.
///
/// The OrthoCamera struct encapsulates the properties of an orthographic camera,
/// including its extent and clipping planes. The extent defines the visible area
/// of the camera in the scene, while the near and far plane offsets define the 
/// range along the Z-axis where objects are rendered.
struct OrthoCamera : public Camera {
    // Enums

    // Public Fields

    // Constructors and Destructors

    /// @brief Constructor.
    /// @param[in] extent The visible area of the camera.
    /// @param[in] nearPlaneOffset The offset of the near clipping plane.
    /// @param[in] farPlaneOffset The offset of the far clipping plane.
    OrthoCamera(const Vec2 resolution = Vec2{1920.0f, 1080.0f},
                const float nearPlaneOffset = 0.1f,
                const float farPlaneOffset = 200.0f)
        : Camera(resolution, nearPlaneOffset, farPlaneOffset) {}

    /// @brief Default deconstructor.
    ~OrthoCamera() override = default;

    // Public Methods

    const glm::mat4 GetProjectionMatrix() const override
    {
        throw std::exception("Method is not implemented yet.");
    }

protected:
    // Protected Fields

    // Protected Methods

private:
    // Private Fields

    // Private Methods
};

} // namespace velecs
