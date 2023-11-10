/// \file    IRenderingSystems.h
/// \author  Matthew Green
/// \date    10/31/2023 12:19:13
/// 
/// \section LICENSE
/// 
/// Copyright (c) 2023 Matthew Green - All rights reserved
/// Unauthorized copying of this file, via any medium is strictly prohibited
/// Proprietary and confidential

#pragma once

#include "velecs/ECS/IECSInterface.h"

#include <vulkan/vulkan_core.h>

#include <SDL2/SDL.h>

#include <glm/mat4x4.hpp>

#include <flecs/flecs.h>

namespace velecs {

/// @class IRenderingECS
/// @brief Interface for rendering systems integrated with ECS.
///
/// This interface defines the core functionality for rendering systems that are
/// meant to work with an ECS framework. It specifies the structure and essential
/// methods that any rendering system should implement, such as obtaining window
/// dimensions and creating rendering contexts.
class IRenderingECS : public IECSInterface {
public:
    // Enums
    // Public Fields

    // Constructors and Destructors

    /// @brief Constructs an IRenderingECS object.
    /// 
    /// This constructor initializes the rendering system with the ECS world and SDL window provided.
    /// @param[in] ecs Reference to the ECS world instance for entity and component management.
    /// @param[in] window Pointer to an initialized SDL_Window for use in rendering.
    IRenderingECS(class IECSManager& ecsManager);
    
    /// @brief Destructor.
    /// 
    /// Ensures that derived classes can be cleaned up correctly through pointers to this interface.
    virtual ~IRenderingECS() = default;

    // Public Methods
    
    /// @brief Retrieves the extent of the window.
    /// 
    /// This method returns the dimensions of the rendering window as a VkExtent2D structure.
    /// @return VkExtent2D The current window extent.
    VkExtent2D const GetWindowExtent() const;

protected:
    // Protected Fields

    VkExtent2D windowExtent{1700, 900}; /// @brief Desired dimensions of the rendering window.

    // Protected Methods
private:
    // Private Fields

    // Private Methods
};

} // namespace velecs
