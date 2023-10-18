
#include "vk_engine.h"

#include "Input/Input.h"
#include "Input/InputActionMap.h"
#include "Input/InputAction.h"

#include <iostream>
#include <unordered_set>

#include <SDL2/SDL.h>
#include <SDL2/SDL_vulkan.h>

#include <vk_types.h>
#include <vk_initializers.h>

using namespace HarvestHavoc::Input;

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

    Input::GetInstance().Init();
    Input::GetInstance().Player->Switch();

    //everything went fine
    _isInitialized = true;
}

void VulkanEngine::cleanup()
{	
    if (_isInitialized) {
        
        SDL_DestroyWindow(_window);
    }
}

void VulkanEngine::input_update()
{
    Input::GetInstance().HandleIEnableDisableRequests();

    Input::GetInstance().TrySettingToIdle();

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
                Input::GetInstance().TryOnPressed(keycode);
            }
            break;
        }
        case SDL_KEYUP:
        {
            SDL_Keycode keycode = event.key.keysym.sym;
            Input::GetInstance().TryOnReleased(keycode);
            break;
        }
        default:
            break;
        }
    }

    Input::GetInstance().TryOnHeld();
}

void VulkanEngine::draw()
{
    //nothing yet
}

void VulkanEngine::run()
{
    while (!isQuitting)
    {
        input_update();

        draw();
    }
}

