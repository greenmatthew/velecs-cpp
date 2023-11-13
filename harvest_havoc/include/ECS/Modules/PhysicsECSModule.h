/// @file    PhysicsECSModule.h
/// @author  Matthew Green
/// @date    2023-11-13 16:15:27
/// 
/// @section LICENSE
/// 
/// Copyright (c) 2023 Matthew Green - All rights reserved
/// Unauthorized copying of this file, via any medium is strictly prohibited
/// Proprietary and confidential

#pragma once

#include "ECS/Modules/IECSModule.h"

namespace hh {

/// @class PhysicsECSModule
/// @brief Brief description.
///
/// Rest of description.
struct PhysicsECSModule : public IECSModule<PhysicsECSModule> {

    PhysicsECSModule(flecs::world& ecs);
};

} // namespace hh
