/// @file    ECSManager.cpp
/// @author  Matthew Green
/// @date    10/30/2023 16:17:43
/// 
/// @section LICENSE
/// 
/// Copyright (c) 2023 Matthew Green - All rights reserved
/// Unauthorized copying of this file, via any medium is strictly prohibited
/// Proprietary and confidential

#include "ECS/ECSManager.h"

#include "ECS/Modules/PipelineECSModule.h"

#include "ECS/Modules/RenderingECSModule.h"
#include "ECS/Modules/InputECSModule.h"
#include "ECS/Modules/PhysicsECSModule.h"

using namespace velecs;

namespace hh {

// Public Fields

// Constructors and Destructors

ECSManager::ECSManager(velecs::VelECSEngine& engine)
    : IECSManager(engine)
{
    // InitPipeline();
    // Do this before importing anything else.
    ecs.import<PipelineECSModule>();

    ecs.import<RenderingECSModule>();
    ecs.import<InputECSModule>();
    ecs.import<PhysicsECSModule>();
}

// Public Methods

void ECSManager::Init()
{
    
}

void ECSManager::Cleanup()
{
    
}

bool ECSManager::GetIsQuitting() const
{
    return ecs.singleton<Input>().get<Input>()->isQuitting;
}

// Protected Fields

// Protected Methods

// Private Fields

// Private Methods

} // namespace hh
