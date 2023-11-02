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

namespace engine {
    class VulkanEngine;
}

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

protected:
    // Protected Fields

    // Constructors

    IRenderingECS(flecs::world& ecs, engine::VulkanEngine& engine) : IECSInterface(ecs), engine(engine) {}

    // Protected Methods

    engine::VulkanEngine& engine;

private:
    // Private Fields

    // Private Methods
};

} // namespace hh
