/// @file    CommonECSModule.h
/// @author  Matthew Green
/// @date    2023-11-15 13:00:34
/// 
/// @section LICENSE
/// 
/// Copyright (c) 2023 Matthew Green - All rights reserved
/// Unauthorized copying of this file, via any medium is strictly prohibited
/// Proprietary and confidential

#pragma once

#include "velecs/ECS/Entity.h"
#include "velecs/ECS/Prefab.h"

#include "velecs/ECS/Components/Rendering/Transform.h"

#include <flecs.h>

namespace velecs {

/// @struct CommonECSModule
/// @brief Brief description.
///
/// Rest of description.
struct CommonECSModule {
public:
    // Enums

    // Public Fields

    // Constructors and Destructors

    /// @brief Constructor.
    CommonECSModule(flecs::world& ecs);

    /// @brief Default deconstructor.
    ~CommonECSModule() = default;

    // Public Methods

protected:
    // Protected Fields

    // Protected Methods

private:
    // Private Fields

    // Private Methods
};

} // namespace velecs
