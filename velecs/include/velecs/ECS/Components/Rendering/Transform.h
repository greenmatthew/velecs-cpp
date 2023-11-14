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

namespace velecs {

/// @struct Transform
/// @brief Brief description.
///
/// Rest of description.
struct Transform {
    Vec3 position{Vec3::ZERO};
    Vec3 rotation{Vec3::ZERO};
    Vec3 scale{Vec3::ONE};
};

} // namespace velecs
