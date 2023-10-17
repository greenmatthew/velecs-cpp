
#include "vk_engine.h"

#include "Input/Input.h"
#include "Input/InputActionMap.h"
#include "Input/InputAction.h"

#include <iostream>

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

    Input::GetInstance().Init();

    //everything went fine
    _isInitialized = true;
}

void VulkanEngine::cleanup()
{	
    if (_isInitialized) {
        
        SDL_DestroyWindow(_window);
    }
}

void VulkanEngine::draw()
{
    //nothing yet
}

void VulkanEngine::run()
{
    SDL_Event event;
    bool bQuit = false;

    //main loop
    while (!bQuit)
    {
        //Handle events on queue
        while (SDL_PollEvent(&event) != 0)
        {
            switch (event.type)
            {
            case SDL_QUIT:
                bQuit = true; //close the window when user alt-f4s or clicks the X button
                break;
            case SDL_KEYDOWN:
            {
                SDL_Keycode keycode = event.key.keysym.sym;
                std::cout << "Key pressed: " << SDL_GetKeyName(keycode) << " (0x" << std::hex << std::uppercase << keycode << ')' << std::endl;
                Input::GetInstance().TryOnPressed(keycode);
                break;
            }
            case SDL_KEYUP:
            {
                SDL_Keycode keycode = event.key.keysym.sym;
                std::cout << "Key released: " << SDL_GetKeyName(keycode) << " (0x" << std::hex << std::uppercase << keycode << ')' << std::endl;
                Input::GetInstance().TryOnReleased(keycode);
                break;
            }
            default:
                break;
            }
        }

        // Input::GetInstance().TryOnHeld(keycode);

        draw();
    }
}

