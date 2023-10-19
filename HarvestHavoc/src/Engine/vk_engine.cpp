/// \file    vk_engine.cpp
/// \author  Matthew Green
/// \date    10/15/2023 14:57:55
/// 
/// \section LICENSE
/// 
/// Copyright (c) 2023 Matthew Green - All rights reserved
/// Unauthorized copying of this file, via any medium is strictly prohibited
/// Proprietary and confidential

#include "Engine/vk_engine.h"

#include "Input/Input.h"
#include "Input/InputActionMap.h"
#include "Input/InputAction.h"

#include <iostream>
#include <unordered_set>

#include <SDL2/SDL.h>
#include <SDL2/SDL_vulkan.h>

#include <Engine/vk_types.h>
#include <Engine/vk_initializers.h>

using namespace HarvestHavoc::Input;

namespace HarvestHavoc::Engine {

// Public Fields

// Constructors and Destructors

// Public Methods

void VulkanEngine::init()
{
    // We initialize SDL and create a window with it. 
    SDL_Init(SDL_INIT_VIDEO);

    SDL_WindowFlags window_flags = (SDL_WindowFlags)(SDL_WINDOW_VULKAN);
    
    _window = SDL_CreateWindow(
        "Vulkan Engine",
        SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,
        _windowExtent.width,
        _windowExtent.height,
        window_flags
    );

    inProcessKeys.reserve(10);

    Input::Input::GetInstance().Init();
    Input::Input::GetInstance().Player->Switch();

    //everything went fine
    _isInitialized = true;
}

void VulkanEngine::cleanup()
{	
    if (_isInitialized) {
        
        SDL_DestroyWindow(_window);
    }
}

void VulkanEngine::run()
{
    while (!isQuitting)
    {
        input_update();

        draw();
    }
}

// Protected Fields

// Protected Methods

// Private Fields

// Private Methods
void VulkanEngine::input_update()
{
    Input::Input::GetInstance().HandleIEnableDisableRequests();

    Input::Input::GetInstance().TrySettingToIdle();

    //Handle events on queue
    while (SDL_PollEvent(&event) != 0)
    {
        switch (event.type)
        {
        case SDL_QUIT:
            isQuitting = true; //close the window when user alt-f4s or clicks the X button
            break;
        case SDL_KEYDOWN:
        {
            SDL_Keycode keycode = event.key.keysym.sym;
            if (event.key.repeat == 0)
            {
                Input::Input::GetInstance().TryOnPressed(keycode);
            }
            break;
        }
        case SDL_KEYUP:
        {
            SDL_Keycode keycode = event.key.keysym.sym;
            Input::Input::GetInstance().TryOnReleased(keycode);
            break;
        }
        default:
            break;
        }
    }

    Input::Input::GetInstance().TryOnHeld();
}

void VulkanEngine::draw()
{
    //nothing yet
}

} // namespace HarvestHavoc::Engine







