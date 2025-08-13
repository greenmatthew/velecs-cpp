/// @file    Engine.hpp
/// @author  Matthew Green
/// @date    2025-05-22 12:50:55
///
/// @section LICENSE
///
/// Copyright (c) 2025 Matthew Green - All rights reserved
/// Unauthorized copying of this file, via any medium is strictly prohibited
/// Proprietary and confidential

#pragma once

#include <velecs/graphics/RenderEngine.hpp>
using velecs::graphics::RenderEngine;

#include <velecs/ecs/World.hpp>
using velecs::ecs::World;

#include <SDL3/SDL_init.h>
#include <SDL3/SDL_events.h>
#include <SDL3/SDL_video.h>

#include <string>
#include <memory>
#include <vector>
#include <optional>

namespace velecs::engine
{
    /// @class Component
    /// @brief Brief description.
    ///
    /// Rest of description.
    class Engine
    {
    public:
        using ConfigurationFunc = std::function<void(Engine&)>;
        using EntryPointFunc = std::function<void()>;
    
        // Enums

        // Public Fields

        // Constructors and Destructors

        /// @brief Default constructor
        Engine() = delete;

        /// @brief Default deconstructor.
        ~Engine() = default;

        // Public Methods

        inline static Engine* Create(int argc, char** argv)
        {
            return new Engine({argv, argv + argc});
        }

        // ---------- Pre-Init ----------

        /// @brief Sets the company name for the application
        /// @param name The company or developer name (e.g., "Epic Games", "YourStudio")
        /// @return Reference to this Engine instance for method chaining
        /// @note This method must be called before initialization, otherwise the application will fail to startup.
        ///       The company name is used for organizing persistent data directories.
        Engine& SetCompanyName(const std::string& name);

        /// @brief Sets the application title
        /// @param title The application name (e.g., "MyGame", "HarvestHavoc")
        /// @return Reference to this Engine instance for method chaining
        /// @note This method must be called before initialization, otherwise the application will fail to startup.
        ///       The app title is used for window titles and persistent data directories.
        Engine& SetAppTitle(const std::string& title);

        /// @brief Sets whether the application will be fullscreen or windowed
        /// @param fullscreen True for fullscreen mode, false for windowed mode
        /// @return Reference to this Engine instance for method chaining
        /// @note If this is set to true, the window width and height will be ignored, however, should still be valid values.
        Engine& SetWindowFullscreen(const bool fullscreen);

        /// @brief Sets the window width in pixels
        /// @param width The desired window width (must be greater than 0)
        /// @return Reference to this Engine instance for method chaining
        Engine& SetWindowWidth(const unsigned int width);

        /// @brief Sets the window height in pixels
        /// @param height The desired window height (must be greater than 0)
        /// @return Reference to this Engine instance for method chaining
        Engine& SetWindowHeight(const unsigned int height);

        /// @brief Sets whether the window can be resized by the user
        /// @param resizable True to allow window resizing, false to make it fixed size
        /// @return Reference to this Engine instance for method chaining
        Engine& SetWindowResizable(const bool resizable);

        template<typename SceneT, typename = IsScene<SceneT>>
        Engine& RegisterScene(const std::string& name, std::optional<size_t> systemCapacity = std::nullopt)
        {
            assert(!_initialized && "Cannot be called after initialization");
            Scene::Create<SceneT>(_world.get(), name, systemCapacity);
            return *this;
        }

        Engine& SetStartingScene(const std::string& name);

        // ---------- Init ----------
        
        Engine& Init();

        // ---------- Post-Init ----------

        template<typename RShaderProgram>
        Engine& RegisterRasterizationShaderProgram(const std::string& name)
        {
            assert(_initialized && "Can only be called after initialization");
            _renderEngine->RegisterRasterizationShaderProgram<RShaderProgram>(name);
            return *this;
        }

        /// @brief SDL application initialization callback wrapper
        /// @param engine Pointer to an already allocated engine instance
        /// @param argc Number of command line arguments
        /// @param argv Array of command line argument strings
        /// @return SDL_APP_CONTINUE on success, SDL_APP_FAILURE on error
        /// @details This function handles SDL app initialization by calling Init() on
        ///          the pre-existing Engine instance. All exceptions are caught and logged.
        /// @note Assumes the engine instance is already allocated and configured
        static SDL_AppResult SDL_AppInit(
            void **engine,
            int argc,
            char** argv,
            ConfigurationFunc configure
        );

        /// @brief SDL application iteration callback wrapper
        /// @param engine Pointer to the engine instance (from SDL_AppInit)
        /// @return SDL_APP_CONTINUE to keep running, SDL_APP_FAILURE on error
        /// @details Called every frame by SDL to update the engine. Handles input processing,
        ///          game logic updates, and rendering. All exceptions are caught and logged.
        static SDL_AppResult SDL_AppIterate(void *engine);

        /// @brief SDL event processing callback wrapper
        /// @param engine Pointer to the engine instance (from SDL_AppInit)
        /// @param event The SDL event to process
        /// @return SDL_APP_CONTINUE normally, SDL_APP_SUCCESS for quit events, SDL_APP_FAILURE on error
        /// @details Processes SDL events including quit requests and forwards other events
        ///          to the engine for input handling. All exceptions are caught and logged.
        static SDL_AppResult SDL_AppEvent(void *engine, SDL_Event *event);

        /// @brief SDL application cleanup callback wrapper
        /// @param engine Pointer to the engine instance (from SDL_AppInit)
        /// @param result The result code from the application run
        /// @details Called when the application is shutting down. Performs cleanup of engine
        ///          resources and deallocates the engine instance. All exceptions are caught and logged.
        static void SDL_AppQuit(void *engine, SDL_AppResult result);

    protected:
        // Protected Fields

        void Update();

        void OnWindowResized();
        inline void OnWindowMaximized() { OnWindowResized(); }
        void OnWindowMinimized();

        // void OnWindowEvent(const SDL_Event event, const SDL_WindowEvent windowEvent);

        // void OnSDLEvent(const SDL_Event event, bool& running);

        Engine& Run();
        Engine& Cleanup();

        // Protected Methods

    private:
        // Private Fields

        bool _initialized{false};

        const std::vector<std::string> _args;

        std::optional<std::string> _companyName;
        std::optional<std::string> _appTitle;
        bool _windowFullscreen{false};
        unsigned int _windowWidth{1280};
        unsigned int _windowHeight{720};
        bool _windowResizable{true};
        std::optional<std::string> _startingScene;

        SDL_Window* _window{nullptr};

        std::unique_ptr<RenderEngine> _renderEngine;
        std::unique_ptr<World> _world;

        // Private Methods

        /// @brief Main constructor
        Engine(const std::vector<std::string>& args);

        SDL_AppResult InitWindow();
        void CleanupWindow();
    };

} // namespace velecs::engine2
