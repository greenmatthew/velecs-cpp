/// \file    Main.cpp
/// \author  Matthew Green
/// \date    10/15/2023 15:30:21
/// 
/// \section LICENSE
/// 
/// Copyright (c) 2023 Matthew Green - All rights reserved
/// Unauthorized copying of this file, via any medium is strictly prohibited
/// Proprietary and confidential

#include <Engine/vk_engine.h>

#include "Input/Input.h"

#include "ECS/Entity.h"

using namespace engine;

int main(int argc, char* argv[])
{
    auto& engine = engine::VulkanEngine::GetInstance();

    engine.Init();

    engine.InitInput(&(hh::Input::Input::GetInstance()));

    {
        auto entity = Entity::Create();
        auto entityPtr = entity.lock();
        if (entityPtr)
        {
            std::cout << entityPtr->name << std::endl;
        }
        else
        {
            std::cout << "No entity exists!" << std::endl;
        }
        
    }

    engine.Run();

    engine.Cleanup();

    return 0;
}
