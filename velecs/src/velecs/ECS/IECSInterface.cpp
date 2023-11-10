/// @file    IECSInterface.cpp
/// @author  Matthew Green
/// @date    2023-11-09 14:48:33
/// 
/// @section LICENSE
/// 
/// Copyright (c) 2023 Matthew Green - All rights reserved
/// Unauthorized copying of this file, via any medium is strictly prohibited
/// Proprietary and confidential

#include "velecs/ECS/IECSInterface.h"
#include "velecs/ECS/IECSManager.h"

namespace velecs {

// Public Fields

// Constructors and Destructors
IECSInterface::IECSInterface(class IECSManager& ecsManager)
    : ecsManager(ecsManager), ecs(ecsManager.ecs) {}


// Public Methods

void IECSInterface::Init()
{
    InitComponents();
    InitSystems();
    InitEntities();
}

// Protected Fields

// Protected Methods

// Private Fields

// Private Methods

} // namespace velecs
