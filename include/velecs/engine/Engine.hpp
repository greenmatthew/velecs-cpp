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

#include <SDL3/SDL_init.h>
#include <SDL3/SDL_events.h>
#include <SDL3/SDL_video.h>

#include <string>
#include <memory>
#include <vector>

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

        /// @brief Default deconstructor.
        ~Engine() = default;

        // Public Methods

        inline static Engine* Create(int argc, char** argv)
        {
            return new Engine({argv, argv + argc});
        }

        /// @brief Sets the application window title
        /// @param title The title to display in the window's title bar
        /// @return Reference to this Engine instance for method chaining
        Engine& SetTitle(const std::string& title);

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

        /// @brief Sets the game entry point function to be called after engine initialization
        /// @param entryPoint Function to call once engine is fully initialized
        /// @return Reference to this Engine instance for method chaining
        Engine& SetEntryPoint(EntryPointFunc entryPoint);

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

        SDL_AppResult Init();

        void Update();

        void ProcessSDLEvent(const SDL_Event& event);

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

        bool _wasInitialized{false};

        const std::vector<std::string> _args;

        std::string _title{"Untitled Velecs Engine Application"};
        bool _windowFullscreen{false};
        unsigned int _windowWidth{1280};
        unsigned int _windowHeight{720};
        bool _windowResizable{true};
        EntryPointFunc _entryPoint{nullptr};

        SDL_Window* _window{nullptr};

        std::unique_ptr<velecs::graphics::RenderEngine> _renderEngine;

        // Private Methods

        /// @brief Default constructor.
        inline Engine(const std::vector<std::string>& args)
            : _args(args) {}

        SDL_AppResult InitWindow();
        void CleanupWindow();
    };

} // namespace velecs::engine2
