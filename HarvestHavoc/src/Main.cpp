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

int main(int argc, char* argv[])
{
    HarvestHavoc::Engine::VulkanEngine engine;

    engine.Init();

    engine.Run();

    engine.Cleanup();

    return 0;
}
