/// @file    InputECSModule.h
/// @author  Matthew Green
/// @date    2023-11-13 13:17:05
/// 
/// @section LICENSE
/// 
/// Copyright (c) 2023 Matthew Green - All rights reserved
/// Unauthorized copying of this file, via any medium is strictly prohibited
/// Proprietary and confidential

#pragma once

#include "ECS/Modules/IECSModule.h"

#include "ECS/Components/Input.h"
#include "ECS/Components/PipelineStages.h"

#include <flecs.h>

#include <iostream>

namespace hh {

/// @struct InputECSModule
/// @brief Manages the input component in the ECS architecture.
///
/// This class is responsible for integrating the Input component with the ECS (Entity Component System),
/// specifically using the Flecs framework. It includes functions for initializing the Input component
/// within the ECS world and updating it based on SDL events.
struct InputECSModule : public IECSModule<InputECSModule> {

    /// @brief Constructs the InputECSModule and initializes the Input component in the ECS world.
    /// @param[in] ecs Reference to the ECS world in which the module operates.
    InputECSModule(flecs::world& ecs);

    /// @brief Static function to update the Input component based on SDL events.
    /// @param[in] e The ECS entity associated with the Input component.
    /// @param[out] input Reference to the Input component to be updated.
    ///
    /// This function handles SDL events, updating the state of the Input component accordingly.
    /// It processes events like SDL_QUIT, SDL_KEYDOWN, and SDL_KEYUP to update the input state.
    static void UpdateInput(flecs::entity e, Input& input);
};

} // namespace hh
