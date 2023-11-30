/// @file    MainCamera.h
/// @author  Matthew Green
/// @date    2023-11-09 16:17:25
/// 
/// @section LICENSE
/// 
/// Copyright (c) 2023 Matthew Green - All rights reserved
/// Unauthorized copying of this file, via any medium is strictly prohibited
/// Proprietary and confidential

#pragma once

#include "velecs/Graphics/Rect.h"

#include <flecs.h>

namespace velecs {

/// @struct MainCamera
/// @brief Brief description.
///
/// Rest of description.
struct MainCamera {
    flecs::entity camera;
    Rect extent;

    MainCamera()
        : camera(flecs::entity::null()), extent(Rect{Vec2::ZERO, Vec2::ZERO}) {}

    MainCamera(flecs::entity cameraEntity, const Rect extent)
        : camera(cameraEntity), extent(extent) {}
};

} // namespace velecs
