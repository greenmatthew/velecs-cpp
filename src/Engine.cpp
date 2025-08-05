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

#include <velecs/common/Paths.hpp>
using namespace velecs::common;

#include <velecs/input/Common.hpp>
using namespace velecs::input;

#include <velecs/math/Vec2.hpp>
using namespace velecs::math;

#include <velecs/ecs/Entity.hpp>
using namespace velecs::ecs;

#include <SDL3/SDL.h>
#include <SDL3/SDL_vulkan.h>

#include <imgui_impl_sdl3.h>

#include <iostream>
#include <stdexcept>

namespace velecs::engine
{

// Public Fields

// Constructors and Destructors

// Public Methods

Engine& Engine::SetCompanyName(const std::string& name)
{
    _companyName = name;
    return *this;
}

Engine& Engine::SetAppTitle(const std::string& title)
{
    _appTitle = title;
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

Engine& Engine::SetStartingScene(const std::string& name)
{
    _startingScene = name;
    return *this;
}

SDL_AppResult Engine::SDL_AppInit(void **engine, int argc, char** argv, ConfigurationFunc configure)
{
    try
    {
        // Create and configure the engine
        Engine* enginePtr = Engine::Create(argc, argv);
        enginePtr->_wasInitialized = true;
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
    try
    {
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
    try
    {
        // Forward event to ImGUI backend
        ImGui_ImplSDL3_ProcessEvent(event);

        switch (event->type)
        {
        case SDL_EVENT_QUIT:
            return SDL_APP_SUCCESS;
        }

        // Forward event to input backend
        Input::ProcessEvent(event);

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

    std::cout << "Exiting..." << std::endl;
}

// Protected Fields

SDL_AppResult Engine::Init()
{
    if (!_appTitle)
    {
        std::cerr << "[ERROR] Must assign an application title" << std::endl;
        return SDL_AppResult::SDL_APP_FAILURE;
    }
    if (!_companyName)  // Changed from if (_companyName) to if (!_companyName)
    {
        std::cerr << "[ERROR] Must assign a company name" << std::endl;
        return SDL_AppResult::SDL_APP_FAILURE;
    }

    Paths::Init(*_companyName, *_appTitle);
    std::cout << "Called Pathes::Init()!" << std::endl;

    // Setup SDL window
    SDL_AppResult result = InitWindow();
    if (result != SDL_AppResult::SDL_APP_CONTINUE) return result;

    _renderEngine = std::make_unique<RenderEngine>(_window);
    result = _renderEngine->Init();
    if (result != SDL_AppResult::SDL_APP_CONTINUE) return result;
    
    // Setup default action profile
    Input::CreateDefaultProfile();

    if (_startingScene)
    {
        auto scene = *_startingScene;
        if (!_sceneManager->TryTransitionScene(scene))
        {
            std::cerr << "[ERROR] Not a valid scene name: '" << scene << "'" << std::endl;
            return SDL_AppResult::SDL_APP_FAILURE;
        }
    }
    else
    {
        std::cerr << "[ERROR] Starting scene not assigned" << std::endl;
        return SDL_AppResult::SDL_APP_FAILURE;
    }

    return result;
}

void Engine::Update()
{
    // 1. Finalize input processing and perform input callbacks
    Input::Update();

    // 2. Process
    _sceneManager->TryProcess(nullptr);

    // 3. Process Rendering
    // Needs to be called somewhere inside Draw() but before the ProcessImGUI code.
    // _sceneManager->TryProcessRendering();
    
    // 4. Process ImGUI
    _renderEngine->StartGUI();
    _sceneManager->TryProcessGUI(nullptr);
    _renderEngine->EndGUI();

    // 5. Render & Present (draws game assets then draws Dear ImGui on top of that then presents)
    _renderEngine->Draw();

    // 6. Cleanup (destroyed marked objects)
    _sceneManager->TryProcessEntityCleanup();
}

void PrintWindowEvent(const std::string& message)
{
    std::cout << "[WindowEvent] " << message << std::endl;
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

Engine& Engine::Cleanup()
{
    // Only attempt to cleanup if initialization flag is on
    if (_wasInitialized)
    {
        if (_renderEngine != nullptr)
        {
            _renderEngine->Cleanup();
            _renderEngine.reset();
        }

        if (_window != nullptr)
        {
            CleanupWindow();
        }

        // Reset initialization flag to prevent accidental double cleanups
        _wasInitialized = false;
    }
    
    return *this;
}

// Protected Methods

// Private Fields

// Private Methods

Engine::Engine(const std::vector<std::string>& args)
    : _args(args)
{
    _sceneManager = std::make_unique<SceneManager>();
}

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

    SDL_SetStringProperty(props, SDL_PROP_WINDOW_CREATE_TITLE_STRING, _appTitle.value().c_str());
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
