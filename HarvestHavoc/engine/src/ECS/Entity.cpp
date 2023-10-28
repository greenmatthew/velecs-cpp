/// \file    Entity.cpp
/// \author  Matthew Green
/// \date    10/27/2023 20:56:01
/// 
/// \section LICENSE
/// 
/// Copyright (c) 2023 Matthew Green - All rights reserved
/// Unauthorized copying of this file, via any medium is strictly prohibited
/// Proprietary and confidential

#include "ECS/Entity.h"
#include "ECS/ECSManager.h"

#include <memory>

namespace engine {

// Public Fields

// Constructors and Destructors

// Public Methods

std::weak_ptr<Entity> Entity::Create()
{
    auto ptr = CreateSharedPtr();
    ECSManager::GetInstance().TrackEntity(ptr);
    return ptr;
}

void Entity::RemoveAllComponents()
{
    components.clear();
}

// Protected Fields

// Protected Methods

// Private Fields

// Private Methods

} // namespace engine
