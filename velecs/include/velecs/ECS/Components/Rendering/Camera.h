/// @file    Camera.h
/// @author  Matthew Green
/// @date    2023-11-22 14:12:41
/// 
/// @section LICENSE
/// 
/// Copyright (c) 2023 Matthew Green - All rights reserved
/// Unauthorized copying of this file, via any medium is strictly prohibited
/// Proprietary and confidential

#pragma once

#include "velecs/Graphics/Rect.h"

#include "velecs/Math/Vec2.h"

namespace velecs {

/// @struct Camera
/// @brief Brief description.
///
/// Rest of description.
struct Camera {
public:
    // Enums

    // Public Fields
    
    float nearPlaneOffset; /// @brief The offset of the near clipping plane along the Z-axis.
    float farPlaneOffset; /// @brief The offset of the far clipping plane along the Z-axis.

    // Constructors and Destructors

    /// @brief Constructor.
    /// @param[in] resolution The visible area of the camera.
    /// @param[in] nearPlaneOffset The offset of the near clipping plane.
    /// @param[in] farPlaneOffset The offset of the far clipping plane.
    Camera(const Vec2 resolution = Vec2{1920.0f, 1080.0f},
                const float nearPlaneOffset = 0.1f,
                const float farPlaneOffset = 200.0f)
        : extent(Rect{ Vec2::ZERO, resolution }),
            nearPlaneOffset(nearPlaneOffset),
            farPlaneOffset(farPlaneOffset),
            aspectRatio(resolution.x / resolution.y) {}

    /// @brief Default deconstructor.
    virtual ~Camera() = default;

    // Public Methods

    const float& GetAspectRatio() const
    {
        return aspectRatio;
    }

    const Vec2& SetResolution(const Vec2 resolution)
    {
        aspectRatio = resolution.x / resolution.y;
        extent = Rect{ Vec2::ZERO, resolution };

        return extent.max;
    }

    const Vec2& GetResolution() const
    {
        return extent.max;
    }

    const Rect& GetExtent() const
    {
        return extent;
    }

protected:
    // Protected Fields

    Rect extent; /// @brief The visible area of the camera in the scene.

    float aspectRatio; /// @brief The aspect ratio of the camera (width / height).

    // Protected Methods

private:
    // Private Fields

    // Private Methods
};

} // namespace velecs
