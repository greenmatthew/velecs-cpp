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
    assert(!_initialized && "Cannot be called after initialization");
    _companyName = name;
    return *this;
}

Engine& Engine::SetAppTitle(const std::string& title)
{
    assert(!_initialized && "Cannot be called after initialization");
    _appTitle = title;
    return *this;
}

Engine& Engine::SetWindowFullscreen(const bool fullscreen)
{
    assert(!_initialized && "Cannot be called after initialization");
    _windowFullscreen = fullscreen;
    return *this;
}

Engine& Engine::SetWindowWidth(const unsigned int width)
{
    assert(!_initialized && "Cannot be called after initialization");
    _windowWidth = width;
    return *this;
}

Engine& Engine::SetWindowHeight(const unsigned int height)
{
    assert(!_initialized && "Cannot be called after initialization");
    _windowHeight = height;
    return *this;
}

Engine& Engine::SetWindowResizable(const bool resizable)
{
    assert(!_initialized && "Cannot be called after initialization");
    _windowResizable = resizable;
    return *this;
}

Engine& Engine::SetStartingScene(const std::string& name)
{
    assert(!_initialized && "Cannot be called after initialization");
    _startingScene = name;
    return *this;
}

Engine& Engine::Init()
{
    if (!_appTitle) throw std::runtime_error("Must assign an application title");
    if (!_companyName) throw std::runtime_error("Must assign a company name");

    Paths::Init(*_companyName, *_appTitle);

    // Setup SDL window
    InitWindow();

    _renderEngine->Init(_window);
    
    // Setup default action profile
    Input::CreateDefaultProfile();

    if (_startingScene)
    {
        auto scene = *_startingScene;
        if (!_world->scenes->TryRequestSceneTransition(scene))
        {
            std::ostringstream oss{};
            oss << "Not a valid scene name: '" << scene << "'";
            throw std::runtime_error(oss.str());
        }
    }
    else
    {
        throw std::runtime_error("Starting scene not assigned");
    }

    _initialized = true;

    return *this;
}

SDL_AppResult Engine::SDL_AppInit(void **engine, int argc, char** argv, ConfigurationFunc configure)
{
    try
    {
        // Create and configure the engine
        Engine* enginePtr = Engine::Create(argc, argv);
        *engine = enginePtr;
        
        // Apply user configuration
        if (configure)
        {
            configure(*enginePtr);
        }
    }
    catch (const std::exception& e) {
        std::cerr << "Error during initialization: " << e.what() << std::endl;
        return SDL_APP_FAILURE;
    }
    catch (...) {
        std::cerr << "Unknown error during initialization" << std::endl;
        return SDL_APP_FAILURE;
    }

    return SDL_APP_CONTINUE;
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

void Engine::Update()
{
    _world->scenes->Internal_TryTransitionIfRequested(nullptr);

    // 1. Finalize input processing and perform input callbacks
    Input::Update();

    // 2. Process
    _world->scenes->Internal_TryProcess(nullptr);

    // 3. Process Rendering
    // Needs to be called somewhere inside Draw() but before the ProcessImGUI code.
    // _sceneManager->TryProcessRendering();
    
    // 4. Process ImGUI
    _renderEngine->StartGUI();
    _world->scenes->Internal_TryProcessGUI(nullptr);
    _renderEngine->EndGUI();

    // 5. Render & Present (draws game assets then draws Dear ImGui on top of that then presents)
    _renderEngine->Draw(_world->scenes->GetCurrentScene());

    // 6. Cleanup (destroyed marked objects)
    _world->scenes->Internal_TryProcessEntityCleanup();
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
    if (_initialized)
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
        _initialized = false;
    }
    
    return *this;
}

// Protected Methods

// Private Fields

// Private Methods

Engine::Engine(const std::vector<std::string>& args)
    : _args(args)
{
    _world = std::make_unique<World>();
    _renderEngine = std::make_unique<RenderEngine>();
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
