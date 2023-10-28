/// \file    ECSManager.cpp
/// \author  Matthew Green
/// \date    10/27/2023 21:49:45
/// 
/// \section LICENSE
/// 
/// Copyright (c) 2023 Matthew Green - All rights reserved
/// Unauthorized copying of this file, via any medium is strictly prohibited
/// Proprietary and confidential

#include "ECS/ECSManager.h"
#include "Core/GameExceptions.h"

namespace engine {

// Public Fields

// Constructors and Destructors

// Public Methods

void ECSManager::Init(VulkanEngine* const engine)
{
    if (isInitialized)
    {
        throw ReinitializationException<ECSManager>();
        return;
    }

    this->engine = engine;

    isInitialized = true;
}

void ECSManager::TrackEntity(std::shared_ptr<Entity> entity)
{
    if (!isInitialized)
    {
        throw UninitializedInstanceException<ECSManager>();
        return;
    }

    engine->TrackEntity(entity);
}

// Protected Fields

// Protected Methods

// Private Fields

// Private Methods

} // namespace engine
