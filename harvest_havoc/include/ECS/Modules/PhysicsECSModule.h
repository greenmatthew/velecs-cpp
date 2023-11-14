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

    /// @struct PhysicsECSModule
    /// @brief Manages the physics system within the ECS framework.
    ///
    /// This module is responsible for integrating and managing physics-related components and systems 
    /// within the ECS (Entity Component System). It is designed to be flexible to accommodate changes 
    /// and additions to physics components and systems in the future. This module focuses on physics 
    /// simulations and does not handle collision detection and response.
    struct PhysicsECSModule : public IECSModule<PhysicsECSModule> {
        /// @brief Initializes the physics module within the ECS world.
        /// @param[in] ecs Reference to the ECS world in which the module operates.
        ///
        /// This constructor sets up the physics module, preparing the ECS world for physics-related 
        /// operations. It is responsible for initializing any necessary components and systems for physics simulation.
        PhysicsECSModule(flecs::world& ecs);
    };

} // namespace hh
