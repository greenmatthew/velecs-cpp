/// \file    Transform.h
/// \author  Matthew Green
/// \date    10/30/2023 19:48:02
/// 
/// \section LICENSE
/// 
/// Copyright (c) 2023 Matthew Green - All rights reserved
/// Unauthorized copying of this file, via any medium is strictly prohibited
/// Proprietary and confidential

#pragma once

#include <Math/Vec3.h>

namespace hh {

/// \struct Transform
/// \brief Brief description.
///
/// Rest of description.
struct Transform {
    engine::Vec3 position{engine::Vec3::ZERO};
    engine::Vec3 rotation{engine::Vec3::ZERO};
    engine::Vec3 scale{engine::Vec3::ONE};
};

} // namespace hh
