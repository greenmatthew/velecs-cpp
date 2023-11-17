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

#include "velecs/Graphics/Rect.h"

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
    // Public Fields

    Rect extent; /// @brief The visible area of the camera in the scene.

    float verticalFov; /// @brief The vertical field of view of the camera in degrees.
    float aspectRatio; /// @brief The aspect ratio of the camera (width / height).

    float nearPlaneOffset; /// @brief The offset of the near clipping plane along the Z-axis.
    float farPlaneOffset; /// @brief The offset of the far clipping plane along the Z-axis.

    // Constructors and Destructors

    /// @brief Constructor.
    /// @param[in] verticalFov The vertical field of view of the camera.
    /// @param[in] aspectRatio The aspect ratio of the camera.
    /// @param[in] nearPlaneOffset The offset of the near clipping plane.
    /// @param[in] farPlaneOffset The offset of the far clipping plane.
    PerspectiveCamera(const Rect extent = Rect{ Vec2::ZERO, Vec2{1920.0f, 1080.0f} },
        const float verticalFov = 70.0f,
        const float aspectRatio = 16.0f / 9.0f,
        const float nearPlaneOffset = 0.1f,
        const float farPlaneOffset = 200.0f)
        : extent(extent),
            verticalFov(verticalFov),
            aspectRatio(aspectRatio),
            nearPlaneOffset(nearPlaneOffset),
            farPlaneOffset(farPlaneOffset) {}

    /// @brief Default deconstructor.
    ~PerspectiveCamera() = default;
};

} // namespace velecs
