/// @file    IECSModule.h
/// @author  Matthew Green
/// @date    2023-11-13 16:18:27
/// 
/// @section LICENSE
/// 
/// Copyright (c) 2023 Matthew Green - All rights reserved
/// Unauthorized copying of this file, via any medium is strictly prohibited
/// Proprietary and confidential

#pragma once

#include <flecs.h>

#include "ECS/Components/PipelineStages.h"

namespace hh {

/// @class IECSModule
/// @brief Brief description.
///
/// Rest of description.
template <typename TECSModule>
struct IECSModule {
public:
    // Enums

    // Public Fields

    // Constructors and Destructors

    IECSModule(flecs::world& ecs)
        : stages(ecs.singleton<PipelineStages>().get<PipelineStages>())
    {
        ecs.import<TECSModule>();
    }

    // Public Methods

protected:
    // Protected Fields

    const PipelineStages * stages;

    // Protected Methods

private:
    // Private Fields

    // Private Methods
};

} // namespace hh
