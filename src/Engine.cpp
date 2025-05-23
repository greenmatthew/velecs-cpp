/// @file    Engine.cpp
/// @author  Matthew Green
/// @date    2025-05-22 12:50:44
///
/// @section LICENSE
///
/// Copyright (c) 2025 Matthew Green - All rights reserved
/// Unauthorized copying of this file, via any medium is strictly prohibited
/// Proprietary and confidential

#include "velecs/engine2/Engine.hpp"

#include "velecs/math/Vec2.hpp"
using namespace velecs::math;

#include <iostream>

#include <SDL2/SDL.h>
#include <SDL2/SDL_vulkan.h>

namespace velecs::engine2
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

    void Engine::OnWindowEvent(const SDL_Event event, const SDL_WindowEvent windowEvent)
    {
        switch (windowEvent.event)
        {
        case SDL_WINDOWEVENT_RESIZED:
            std::cout << "Window resized to: " << windowEvent.data1 << "x" << windowEvent.data2 << std::endl;
            // OnWindowResized();
            break;
        
        case SDL_WINDOWEVENT_MAXIMIZED:
            // OnWindowMaximized();
            break;
        
        case SDL_WINDOWEVENT_MINIMIZED:
            // OnWindowMinimized();
            break;
        
        case SDL_WINDOWEVENT_MOVED:
            std::cout << "Window moved to: " << Vec2(static_cast<float>(windowEvent.data1), static_cast<float>(windowEvent.data2)) << std::endl;
            break;
        
        default:
            std::cout << "Unhandled window event: " << (SDL_WindowEventID)windowEvent.event << std::endl;
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
                OnSDLEvent(event, running);
            }
            
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
