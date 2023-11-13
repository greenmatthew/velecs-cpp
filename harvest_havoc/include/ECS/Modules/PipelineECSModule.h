/// @file    PipelineECSModule.h
/// @author  Matthew Green
/// @date    2023-11-13 14:28:45
/// 
/// @section LICENSE
/// 
/// Copyright (c) 2023 Matthew Green - All rights reserved
/// Unauthorized copying of this file, via any medium is strictly prohibited
/// Proprietary and confidential

#pragma once

#include "ECS/Components/PipelineStages.h"

#include <flecs.h>

#include <iostream>

namespace hh {

/// @class PipelineECSModule
/// @brief Brief description.
///
/// Rest of description.
struct PipelineECSModule {

    /// @brief Constructor.
    PipelineECSModule(flecs::world& ecs);
};

} // namespace hh
