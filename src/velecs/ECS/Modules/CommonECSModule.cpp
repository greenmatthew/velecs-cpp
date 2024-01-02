/// @file    CommonECSModule.cpp
/// @author  Matthew Green
/// @date    2023-11-15 13:08:59
/// 
/// @section LICENSE
/// 
/// Copyright (c) 2023 Matthew Green - All rights reserved
/// Unauthorized copying of this file, via any medium is strictly prohibited
/// Proprietary and confidential

#include "velecs/ECS/Modules/CommonECSModule.h"

#include <iostream>

namespace velecs {

// Public Fields

// Constructors and Destructors

CommonECSModule::CommonECSModule(flecs::world& ecs)
{
    ecs.import<CommonECSModule>();
    std::cout << "[INFO] [ECSManager] Started import of '" << typeid(CommonECSModule).name() << "' ECS module on flecs::world::id(): " << ecs.id() << " @ 0x" << ecs.c_ptr() << '.' << std::endl;

    ecs.component<Transform>();
    
    Entity::Init(ecs);
    Prefab::Init(ecs);
}

// Public Methods

// Protected Fields

// Protected Methods

// Private Fields

// Private Methods

} // namespace velecs
