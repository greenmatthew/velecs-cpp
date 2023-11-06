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

#include "ECS/IECSInterface.h"

#include <glm/mat4x4.hpp>

namespace hh {

/// \class IRenderingSystems
/// \brief Brief description.
///
/// Rest of description.
class IRenderingECS : public IECSInterface {
public:
    // Enums

    // Public Fields

    // Destructors
    
    /// \brief Default deconstructor.
    virtual ~IRenderingECS() = default;

    // Public Methods

    VkExtent2D const GetWindowExtent() const;

protected:
    // Protected Fields

    SDL_Window* const window;
    VkExtent2D _windowExtent{1700, 900}; /// \brief Desired dimensions of the rendering window.

    // Constructors

    IRenderingECS(flecs::world& ecs, SDL_Window* const window) : IECSInterface(ecs), window(window) {}

    // Protected Methods
private:
    // Private Fields

    // Private Methods
};

} // namespace hh
