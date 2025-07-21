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

#include <velecs/math/Vec2.hpp>
using namespace velecs::math;

#include <velecs/input/Common.hpp>
using namespace velecs::input;

#include <velecs/common/Paths.hpp>
using namespace velecs::common;

#include <SDL3/SDL.h>
#include <SDL3/SDL_vulkan.h>

#include <iostream>
#include <stdexcept>

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

Engine& Engine::SetEntryPoint(EntryPointFunc entryPoint)
{
    _entryPoint = entryPoint;
    return *this;
}

SDL_AppResult Engine::SDL_AppInit(void **engine, int argc, char** argv, ConfigurationFunc configure)
{
    try {
        // Create and configure the engine
        Engine* enginePtr = Engine::Create(argc, argv);
        *engine = enginePtr;
        
        // Apply user configuration
        if (configure)
        {
            configure(*enginePtr);
        }

        return enginePtr->Init();
    }
    catch (const std::exception& e) {
        std::cerr << "Error during initialization: " << e.what() << std::endl;
        return SDL_APP_FAILURE;
    }
    catch (...) {
        std::cerr << "Unknown error during initialization" << std::endl;
        return SDL_APP_FAILURE;
    }
}

SDL_AppResult Engine::SDL_AppIterate(void *engine)
{
    try {
        Engine& engineRef = *static_cast<Engine*>(engine);
        engineRef.Update();
        return SDL_APP_CONTINUE;
    }
    catch (const std::exception& e) {
        std::cerr << "Error during update: " << e.what() << std::endl;
        return SDL_APP_FAILURE; // This will cause SDL to quit gracefully
    }
    catch (...) {
        std::cerr << "Unknown error during update" << std::endl;
        return SDL_APP_FAILURE;
    }
}

SDL_AppResult Engine::SDL_AppEvent(void *engine, SDL_Event *event)
{
    try {
        switch (event->type)
        {
        case SDL_EVENT_QUIT:
            return SDL_APP_SUCCESS;
        }

        Engine& engineRef = *static_cast<Engine*>(engine);
        engineRef.ProcessSDLEvent(*event);
        return SDL_APP_CONTINUE;
    }
    catch (const std::exception& e) {
        std::cerr << "Error during event processing: " << e.what() << std::endl;
        return SDL_APP_FAILURE;
    }
    catch (...) {
        std::cerr << "Unknown error during event processing" << std::endl;
        return SDL_APP_FAILURE;
    }
}

void Engine::SDL_AppQuit(void *engine, SDL_AppResult result)
{
    try
    {
        Engine* enginePtr = static_cast<Engine*>(engine);
        enginePtr->Cleanup();
        delete enginePtr;
    }
    catch (const std::exception& e) {
        std::cerr << "Error during app quit: " << e.what() << std::endl;
    }
    catch (...) {
        std::cerr << "Unknown error during app quit" << std::endl;
    }
}

// Protected Fields

SDL_AppResult Engine::Init()
{
    Paths::Initialize(_args[0]);

    // Setup SDL window
    SDL_AppResult result = InitWindow();
    if (result != SDL_AppResult::SDL_APP_CONTINUE) return result;

    _renderEngine = std::make_unique<velecs::graphics::RenderEngine>(_window);
    result = _renderEngine->Init();
    if (result != SDL_AppResult::SDL_APP_CONTINUE) return result;
    
    // Setup default action profile
    Input::CreateDefaultProfile();

    // Entry point is required - throw clear error if not set
    if (_entryPoint == nullptr)
    {
        throw std::runtime_error(
            "Missing required application entry point. "
            "You must call SetEntryPoint() on your Engine instance before initialization. "
            "Example: engine.SetEntryPoint(YourGameInitFunction);"
        );
    }

    // Call user entry point after engine is fully initialized
    try
    {
        _entryPoint();
    }
    catch (const std::exception& e)
    {
        std::cerr << "Error in application entry point: " << e.what() << std::endl;
        return SDL_APP_FAILURE;
    }

    return result;
}

void Engine::Update()
{
    Input::Update();
    _renderEngine->Draw();
}

void PrintWindowEvent(const std::string& message)
{
    std::cout << "[WindowEvent] " << message << std::endl;
}

void Engine::ProcessSDLEvent(const SDL_Event& event)
{
    // Forward event to ImGUI backend
    // ImGui_ImplSDL2_ProcessEvent(&event);
    
    // Process system events
    // OnSDLEvent(event, running);

    Input::ProcessEvent(event);
}

// void Engine::OnWindowEvent(const SDL_Event event, const SDL_WindowEvent windowEvent)
// {
//     switch (windowEvent.type)
//     {
//     case SDL_EVENT_WINDOW_SHOWN:
//         PrintWindowEvent("Window opened.");
//         break;

//     case SDL_EVENT_WINDOW_FOCUS_GAINED:
//         PrintWindowEvent("Window gained focus.");
//         break;
    
//     case SDL_EVENT_WINDOW_FOCUS_LOST:
//         PrintWindowEvent("Window lost focus.");
//         break;
    
//     case SDL_EVENT_WINDOW_MOUSE_ENTER:
//         PrintWindowEvent("Mouse entered window.");
//         break;

//     case SDL_EVENT_WINDOW_MOUSE_LEAVE:
//         PrintWindowEvent("Mouse left window.");
//         break;
    
//     case SDL_EVENT_WINDOW_RESIZED:
//     {
//         std::string newRes = std::to_string(windowEvent.data1) + "x" + std::to_string(windowEvent.data2);
//         PrintWindowEvent("Window resized to: " + newRes);
//         // OnWindowResized();
//         break;
//     }
//     case SDL_EVENT_WINDOW_PIXEL_SIZE_CHANGED:
//     {
//         std::string newRes = std::to_string(windowEvent.data1) + "x" + std::to_string(windowEvent.data2);
//         PrintWindowEvent("Window size changed to: " + newRes);
//         // OnWindowResized();
//         break;
//     }
//     case SDL_EVENT_WINDOW_MAXIMIZED:
//         PrintWindowEvent("Window maximized.");
//         // OnWindowMaximized();
//         break;
    
//     case SDL_EVENT_WINDOW_MINIMIZED:
//         PrintWindowEvent("Window minimized.");
//         // OnWindowMinimized();
//         break;
    
//     case SDL_EVENT_WINDOW_RESTORED:
//         PrintWindowEvent("Window has been restored to normal size and position.");
//         break;
    
//     case SDL_EVENT_WINDOW_MOVED:
//     {
//         Vec2 newPos = Vec2(static_cast<float>(windowEvent.data1), static_cast<float>(windowEvent.data2));
//         PrintWindowEvent("Window moved to: " + newPos.ToString());
//         break;
//     }
//     case SDL_EVENT_WINDOW_EXPOSED:
//         PrintWindowEvent("Window exposed (should be redrawn).");
//         break;
    
//     case SDL_EVENT_WINDOW_CLOSE_REQUESTED:
//         PrintWindowEvent("Window closing.");
//         break;
    
//     default:
//         PrintWindowEvent("Unhandled window event: " + std::to_string(windowEvent.event));
//         break;
//     }
// }

// void Engine::OnSDLEvent(const SDL_Event event, bool& running)
// {
//     switch (event.type)
//     {
//     case SDL_EVENT_QUIT:
//         running = false;
//         break;
    
//     // case SDL_WINDOW_EVENT:
//     //     // Probably forward/handle this in velecs-rendering in future...
//     //     OnWindowEvent(event, event.window);
//     //     break;
//     }
// }

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
            // OnSDLEvent(event, running);

            // Forward event to velecs-input for processing keyboard, mouse, controller, and joystick type events
            Input::ProcessEvent(event);
        }

        // velecs::rendering::RenderNextFrame();

        // Always call at the END of the frame
        // Call update once per frame after all events processed
        Input::Update();

        // Small delay to prevent 100% CPU usage
        SDL_Delay(16); // ~60 FPS
    }

    return *this;
}

Engine& Engine::Cleanup()
{
    if (_renderEngine != nullptr)
    {
        _renderEngine->Cleanup();
    }

    if (_window != nullptr)
    {
        CleanupWindow();
    }
    
    return *this;
}

// Protected Methods

// Private Fields

// Private Methods

SDL_AppResult Engine::InitWindow()
{
    // We initialize SDL and create a window with it. 
    if (!SDL_Init(SDL_INIT_VIDEO))
    {
        SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
        return SDL_AppResult::SDL_APP_FAILURE;
    }

    SDL_PropertiesID props = SDL_CreateProperties();
    if(props == 0)
    {
        SDL_Log("Unable to create properties: %s", SDL_GetError());
        return SDL_AppResult::SDL_APP_FAILURE;
    }

    SDL_SetStringProperty(props, SDL_PROP_WINDOW_CREATE_TITLE_STRING, _title.c_str());
    SDL_SetBooleanProperty(props, SDL_PROP_WINDOW_CREATE_FULLSCREEN_BOOLEAN, _windowFullscreen);
    SDL_SetBooleanProperty(props, SDL_PROP_WINDOW_CREATE_RESIZABLE_BOOLEAN, true);
    SDL_SetNumberProperty(props, SDL_PROP_WINDOW_CREATE_WIDTH_NUMBER, _windowWidth);
    SDL_SetNumberProperty(props, SDL_PROP_WINDOW_CREATE_HEIGHT_NUMBER, _windowHeight);
    SDL_SetBooleanProperty(props, SDL_PROP_WINDOW_CREATE_VULKAN_BOOLEAN, true);

    _window = SDL_CreateWindowWithProperties(props);

    if(_window == nullptr)
    {
        SDL_Log("Unable to create window: %s", SDL_GetError());
        return SDL_AppResult::SDL_APP_FAILURE;
    }

    return SDL_AppResult::SDL_APP_CONTINUE;
}

void Engine::CleanupWindow()
{
    SDL_DestroyWindow(_window);

    if (_renderEngine != nullptr)
    {
        _renderEngine->Cleanup();
        _renderEngine.reset();
    }
}

} // namespace velecs::engine2
