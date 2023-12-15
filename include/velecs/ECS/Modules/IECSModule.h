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

#include "velecs/ECS/Modules/PipelineECSModule.h"
#include "velecs/ECS/Modules/CommonECSModule.h"

#include "velecs/ECS/Entity.h"

#include <flecs.h>

namespace velecs {

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
        : ecsPtr(&ecs)
    {
        static_assert(std::is_base_of<IECSModule, TECSModule>::value, "TECSModule must be a subclass of IECSModule");

        ecs.import<PipelineECSModule>();

        stages = ecs.singleton<PipelineStages>().get<PipelineStages>();

        ecs.import<CommonECSModule>();

        ecs.import<TECSModule>();
        std::cout << "[INFO] [ECSManager] Started import of '" << typeid(TECSModule).name() << "' ECS module on flecs::world::id(): " << ecs.id() << " @ 0x" << ecs.c_ptr() << '.' << std::endl;
    }

    // Public Methods

protected:
    // Protected Fields

    const PipelineStages * stages;

    // Protected Methods

    flecs::world& ecs()
    {
        return *ecsPtr;
    }

private:
    // Private Fields

    flecs::world* ecsPtr;

    // Private Methods
};

} // namespace velecs
