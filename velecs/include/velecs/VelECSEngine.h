/// \file    VelECSEngine.h
/// \author  Matthew Green
/// \date    10/19/2023 14:58:06
/// 
/// \section LICENSE
/// 
/// Copyright (c) 2023 Matthew Green - All rights reserved
/// Unauthorized copying of this file, via any medium is strictly prohibited
/// Proprietary and confidential

#pragma once

#include "velecs/Memory/DeletionQueue.h"

#include "velecs/Rendering/MeshPushConstants.h"

#include <vulkan/vulkan_core.h>

#include <SDL2/SDL.h>

#include <vector>
#include <memory>

namespace velecs {

/// \class VelECSEngine
/// \brief Brief description.
///
/// Rest of description.
class VelECSEngine {
public:
    // Enums

    // Public Fields

    // Constructors and Destructors

    VelECSEngine() = default;
    ~VelECSEngine() = default;

    // Delete the copy constructor and assignment operator to prevent copies
    VelECSEngine(const VelECSEngine&) = delete;
    VelECSEngine& operator=(const VelECSEngine&) = delete;
    
    // Public Methods

    /// \brief Sets the ECS Manager.
    /// \param ecsManager A unique pointer to an IECSManager implementation.
    /// \return Reference to the VelECSEngine instance, allowing for method chaining.
    ///
    /// This method assigns the ECS Manager which will handle the creation and processing
    /// of components, entities, and systems within the ECS architecture.
    VelECSEngine& SetECS(std::unique_ptr<class IECSManager> ecsManager);

    /// \brief Runs the main event and rendering loop, handling input and drawing frames.
    /// \return Reference to the VelECSEngine instance, allowing for method chaining.
    ///
    /// This method enters a loop which processes SDL2 events, updates the engine state, and renders frames to the screen.
    /// It continues looping until a quit event is received, at which point it returns control to the caller.
    VelECSEngine& Run();

protected:
    // Protected Fields

    // Protected Methods

private:
    // Private Fields

    // std::unique_ptr<IInput> input;
    std::unique_ptr<IECSManager> ecsManager;

    // Private Methods
};

} // namespace velecs
