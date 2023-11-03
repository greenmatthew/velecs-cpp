/// \file    OrthoCamera.h
/// \author  Matthew Green
/// \date    11/01/2023 17:51:07
/// 
/// \section LICENSE
/// 
/// Copyright (c) 2023 Matthew Green - All rights reserved
/// Unauthorized copying of this file, via any medium is strictly prohibited
/// Proprietary and confidential

#pragma once

#include <Graphics/Rect.h>

#include <Math/Vec2.h>

namespace hh {

/// \class OrthoCamera
/// \brief Represents an orthographic camera.
///
/// The OrthoCamera struct encapsulates the properties of an orthographic camera,
/// including its extent and clipping planes. The extent defines the visible area
/// of the camera in the scene, while the near and far plane offsets define the 
/// range along the Z-axis where objects are rendered.
struct OrthoCamera {
    // Public Fields

    velecs::Rect extent; /// \brief The visible area of the camera in the scene.
    
    float nearPlaneOffset; /// \brief The offset of the near clipping plane along the Z-axis.
    float farPlaneOffset; /// \brief The offset of the far clipping plane along the Z-axis.

    // Constructors and Destructors

    /// \brief Constructor.
    /// \param[in] extent The visible area of the camera.
    /// \param[in] nearPlaneOffset The offset of the near clipping plane.
    /// \param[in] farPlaneOffset The offset of the far clipping plane.
    OrthoCamera(const velecs::Rect& extent = {velecs::Vec2::zero(), velecs::Vec2{1920.0f, 1080.0f}},
                const float nearPlaneOffset = 0.1f,
                const float farPlaneOffset = 200.0f)
        : extent(extent), nearPlaneOffset(nearPlaneOffset), farPlaneOffset(farPlaneOffset) {}

    /// \brief Default deconstructor.
    ~OrthoCamera() = default;
};

} // namespace hh
