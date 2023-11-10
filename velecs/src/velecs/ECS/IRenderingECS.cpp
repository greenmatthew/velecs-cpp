/// @file    IRenderingECS.cpp
/// @author  Matthew Green
/// @date    2023-11-09 15:04:31
/// 
/// @section LICENSE
/// 
/// Copyright (c) 2023 Matthew Green - All rights reserved
/// Unauthorized copying of this file, via any medium is strictly prohibited
/// Proprietary and confidential

#include "velecs/ECS/IRenderingECS.h"

#include "velecs/ECS/IECSManager.h"

namespace velecs {

// Public Fields

// Constructors and Destructors

IRenderingECS::IRenderingECS(IECSManager& ecsManager)
    : IECSInterface(ecsManager) {}

// Public Methods

VkExtent2D const IRenderingECS::GetWindowExtent() const
{
    return windowExtent;
}

// Protected Fields

// Protected Methods

// Private Fields

// Private Methods

} // namespace velecs
