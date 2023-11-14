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

#include <type_traits>

namespace hh {

/// @struct IECSModule
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
        static_assert(std::is_base_of<IECSModule, TECSModule>::value, "TECSModule must be a subclass of IECSModule");

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
