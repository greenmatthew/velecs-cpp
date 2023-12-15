/// @file    VelECSEngine.cpp
/// @author  Matthew Green
/// @date    10/15/2023 14:57:55
/// 
/// @section LICENSE
/// 
/// Copyright (c) 2023 Matthew Green - All rights reserved
/// Unauthorized copying of this file, via any medium is strictly prohibited
/// Proprietary and confidential

#include "velecs/VelECSEngine.h"
#include "velecs/Engine/vk_initializers.h"
#include "velecs/Rendering/PipelineBuilder.h"
#include "velecs/Rendering/ShaderModule.h"
#include "velecs/ECS/IECSManager.h"
#include "velecs/FileManagement/Path.h"

#include <iostream>
#include <fstream>
#include <chrono>

#include <SDL2/SDL.h>
#include <SDL2/SDL_vulkan.h>

#include <VkBootstrap.h>

#include <imgui.h>
#include <backends/imgui_impl_sdl2.h>
#include <backends/imgui_impl_vulkan.h>

namespace velecs {

// Public Fields

// Constructors and Destructors

// Public Methods

VelECSEngine& VelECSEngine::SetECS(std::unique_ptr<IECSManager> ecsManager)
{
    this->ecsManager = std::move(ecsManager);
    return *this;
}

VelECSEngine& VelECSEngine::Run()
{
    auto lastFrameTime = std::chrono::high_resolution_clock::now();

    while (!ecsManager->GetIsQuitting())
    {
        auto currentFrameTime = std::chrono::high_resolution_clock::now();
        std::chrono::duration<float> elapsedTime = currentFrameTime - lastFrameTime;
        float deltaTime = elapsedTime.count();

        lastFrameTime = currentFrameTime;

        ecsManager->ecs.progress(deltaTime);
    }
    return *this;
}

// Protected Fields

// Protected Methods

// Private Fields

// Private Methods

} // namespace velecs
