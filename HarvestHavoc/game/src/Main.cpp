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

#include "Graphics/Color32.h";

int main(int argc, char* argv[])
{
    std::cout << sizeof(engine::Graphics::Color32) << std::endl;

    auto& engine = engine::Engine::VulkanEngine::GetInstance();

    engine.Init();

    engine.InitInput(&(hh::Input::Input::GetInstance()));

    engine.Run();

    engine.Cleanup();

    return 0;
}
