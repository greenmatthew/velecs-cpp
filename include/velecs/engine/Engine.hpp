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

    protected:
        // Protected Fields

        // Protected Methods

    private:
        // Private Fields

        const std::vector<std::string> _args;

        std::string _title{"Unnamed Application"};
        bool _windowFullscreen{false};
        unsigned int _windowWidth{1280};
        unsigned int _windowHeight{720};
        bool _windowResizable{true};

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
