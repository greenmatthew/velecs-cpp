/// @file    Engine.cpp
/// @author  Matthew Green
/// @date    2025-05-22 12:50:44
///
/// @section LICENSE
///
/// Copyright (c) 2025 Matthew Green - All rights reserved
/// Unauthorized copying of this file, via any medium is strictly prohibited
/// Proprietary and confidential

#include "velecs/engine/Engine.hpp"

#include "velecs/math/Vec2.hpp"
using namespace velecs::math;

#include "velecs/input/Input.hpp"
using namespace velecs::input;

#include <iostream>

#include <SDL2/SDL.h>
#include <SDL2/SDL_vulkan.h>

namespace velecs::engine
{

    // Public Fields

    // Constructors and Destructors

    // Public Methods

    Engine& Engine::SetTitle(const std::string& title)
    {
        this->_title = title;
        return *this;
    }

    Engine& Engine::SetWindowFullscreen(const bool fullscreen)
    {
        _windowFullscreen = fullscreen;
        return *this;
    }

    Engine& Engine::SetWindowWidth(const unsigned int width)
    {
        _windowWidth = width;
        return *this;
    }

    Engine& Engine::SetWindowHeight(const unsigned int height)
    {
        _windowHeight = height;
        return *this;
    }

    Engine& Engine::SetWindowResizable(const bool resizable)
    {
        _windowResizable = resizable;
        return *this;
    }

    Engine& Engine::Init()
    {
        InitWindow();
        return *this;
    }

    void PrintWindowEvent(const std::string& message)
    {
        std::cout << "[WindowEvent] " << message << std::endl;
    }

    void Engine::OnWindowEvent(const SDL_Event event, const SDL_WindowEvent windowEvent)
    {
        switch (windowEvent.event)
        {
        case SDL_WINDOWEVENT_SHOWN:
            PrintWindowEvent("Window opened.");
            break;

        case SDL_WINDOWEVENT_FOCUS_GAINED:
            PrintWindowEvent("Window gained focus.");
            break;
        
        case SDL_WINDOWEVENT_FOCUS_LOST:
            PrintWindowEvent("Window lost focus.");
            break;
        
        case SDL_WINDOWEVENT_ENTER:
            PrintWindowEvent("Mouse entered window.");
            break;

        case SDL_WINDOWEVENT_LEAVE:
            PrintWindowEvent("Mouse left window.");
            break;
        
        case SDL_WINDOWEVENT_RESIZED:
        {
            std::string newRes = std::to_string(windowEvent.data1) + "x" + std::to_string(windowEvent.data2);
            PrintWindowEvent("Window resized to: " + newRes);
            // OnWindowResized();
            break;
        }
        case SDL_WINDOWEVENT_SIZE_CHANGED:
        {
            std::string newRes = std::to_string(windowEvent.data1) + "x" + std::to_string(windowEvent.data2);
            PrintWindowEvent("Window size changed to: " + newRes);
            // OnWindowResized();
            break;
        }
        case SDL_WINDOWEVENT_MAXIMIZED:
            PrintWindowEvent("Window maximized.");
            // OnWindowMaximized();
            break;
        
        case SDL_WINDOWEVENT_MINIMIZED:
            PrintWindowEvent("Window minimized.");
            // OnWindowMinimized();
            break;
        
        case SDL_WINDOWEVENT_RESTORED:
            PrintWindowEvent("Window has been restored to normal size and position.");
            break;
        
        case SDL_WINDOWEVENT_MOVED:
        {
            Vec2 newPos = Vec2(static_cast<float>(windowEvent.data1), static_cast<float>(windowEvent.data2));
            PrintWindowEvent("Window moved to: " + newPos.ToString());
            break;
        }
        case SDL_WINDOWEVENT_EXPOSED:
            PrintWindowEvent("Window exposed (should be redrawn).");
            break;
        
        case SDL_WINDOWEVENT_CLOSE:
            PrintWindowEvent("Window closing.");
            break;
        
        default:
            PrintWindowEvent("Unhandled window event: " + std::to_string(windowEvent.event));
            break;
        }
    }

    void Engine::OnSDLEvent(const SDL_Event event, bool& running)
    {
        switch (event.type)
        {
        case SDL_QUIT:
            running = false;
            break;
        
        case SDL_WINDOWEVENT:
            // Probably forward/handle this in velecs-rendering in future...
            OnWindowEvent(event, event.window);
            break;
        }
    }

    Engine& Engine::Run()
    {
        bool running = true;
        SDL_Event event;
    
        while (running)
        {
            while (SDL_PollEvent(&event))
            {
                // Forward event to ImGUI backend
                // ImGui_ImplSDL2_ProcessEvent(&event);
                
                // Process system events
                OnSDLEvent(event, running);

                // Forward event to velecs-input for processing keyboard, mouse, controller, and joystick type events
                Input::ProcessEvent(event);
            }

            // Call update once per frame after all events processed
            Input().Update();

            // velecs::rendering::RenderNextFrame();

            // Small delay to prevent 100% CPU usage
            SDL_Delay(16); // ~60 FPS
        }

        return *this;
    }

    Engine& Engine::Cleanup()
    {
        CleanupWindow();
        return *this;
    }

    // Protected Fields

    // Protected Methods

    // Private Fields

    // Private Methods

    void Engine::InitWindow()
    {
        // We initialize SDL and create a window with it. 
        SDL_Init(SDL_INIT_VIDEO);

        int flags = SDL_WINDOW_VULKAN;
        if (_windowFullscreen) flags |= SDL_WINDOW_FULLSCREEN;
        if (_windowResizable) flags |= SDL_WINDOW_RESIZABLE;

        _window = SDL_CreateWindow(
            _title.c_str(),
            SDL_WINDOWPOS_UNDEFINED,
            SDL_WINDOWPOS_UNDEFINED,
            _windowWidth,
            _windowHeight,
            flags
        );
        if (_window == nullptr)
        {
            std::cerr << "Failed to create window. SDL Error: " << SDL_GetError() << "\n";
            exit(EXIT_FAILURE);
        }

        if (SDL_Init(SDL_INIT_VIDEO) != 0)
        {
            std::cerr << "Failed to initialize SDL. SDL Error: " << SDL_GetError() << "\n";
            exit(EXIT_FAILURE);
        }
    }

    void Engine::CleanupWindow()
    {
        SDL_DestroyWindow(_window);
    }

} // namespace velecs::engine2
