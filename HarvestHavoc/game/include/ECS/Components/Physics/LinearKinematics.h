/// \file    LinearKinematics.h
/// \author  Matthew Green
/// \date    10/30/2023 19:48:10
/// 
/// \section LICENSE
/// 
/// Copyright (c) 2023 Matthew Green - All rights reserved
/// Unauthorized copying of this file, via any medium is strictly prohibited
/// Proprietary and confidential

#pragma once

#include <Math/Vec3.h>

namespace hh {

/// \struct LinearKinematics
/// \brief Brief description.
///
/// Rest of description.
struct LinearKinematics {
    engine::Vec3 velocity{engine::Vec3::ZERO};
    engine::Vec3 acceleration{engine::Vec3::ZERO};
};

} // namespace hh
