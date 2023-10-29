/// \file    Component.cpp
/// \author  Matthew Green
/// \date    10/27/2023 20:59:59
/// 
/// \section LICENSE
/// 
/// Copyright (c) 2023 Matthew Green - All rights reserved
/// Unauthorized copying of this file, via any medium is strictly prohibited
/// Proprietary and confidential

#include "ECS/Component.h"
#include "ECS/Entity.h"

namespace engine {

// Public Fields

// Constructors and Destructors

Component::Component(std::weak_ptr<Entity> entity)
    : entity(entity) {}

// Public Methods

std::weak_ptr<Entity> Component::GetEntity()
{
    return entity;
}

// Protected Fields

// Protected Methods

// Private Fields

// Private Methods

} // namespace engine
