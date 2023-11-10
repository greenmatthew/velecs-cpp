/// \file    VelECSEngine.h
/// \author  Matthew Green
/// \date    10/19/2023 14:58:06
/// 
/// \section LICENSE
/// 
/// Copyright (c) 2023 Matthew Green - All rights reserved
/// Unauthorized copying of this file, via any medium is strictly prohibited
/// Proprietary and confidential

#pragma once

#include "velecs/Memory/DeletionQueue.h"

#include "velecs/Rendering/MeshPushConstants.h"

#include <vulkan/vulkan_core.h>

#include <SDL2/SDL.h>

#include <vector>
#include <memory>

namespace velecs {

/// \class VelECSEngine
/// \brief Brief description.
///
/// Rest of description.
class VelECSEngine {
public:
    // Enums

    // Public Fields

    // Delete the copy constructor and assignment operator to prevent copies
    VelECSEngine(const VelECSEngine&) = delete;
    VelECSEngine& operator=(const VelECSEngine&) = delete;
    
    // Public Methods

    /// \brief Provide a static method to access the singleton instance
    static VelECSEngine& GetInstance() {
        static VelECSEngine instance;  // Guaranteed to be destroyed, instantiated on first use.
        return instance;
    }

    /// \brief Initializes the engine, setting up necessary Vulkan objects and other resources.
    ///
    /// This method sets up Vulkan, SDL2, and other critical structures required for rendering and processing.
    /// It should be called before attempting to use any other methods of this class.
    /// \return Reference to the VelECSEngine instance, allowing for method chaining.
    VelECSEngine& Init();

    /// \brief Initializes input handling.
    /// \return Reference to the VelECSEngine instance, allowing for method chaining.
    ///
    /// This method sets up SDL2 event handling for processing user input.
    /// It is called by the Init method during engine initialization.
    // VelECSEngine& SetInput(std::unique_ptr<IInput> inputHandle);

    /// \brief Sets the ECS Manager.
    /// \param ecsManager A unique pointer to an IECSManager implementation.
    /// \return Reference to the VelECSEngine instance, allowing for method chaining.
    ///
    /// This method assigns the ECS Manager which will handle the creation and processing
    /// of components, entities, and systems within the ECS architecture.
    VelECSEngine& SetECS(std::unique_ptr<class IECSManager> ecsManager);

    /// \brief Runs the main event and rendering loop, handling input and drawing frames.
    /// \return Reference to the VelECSEngine instance, allowing for method chaining.
    ///
    /// This method enters a loop which processes SDL2 events, updates the engine state, and renders frames to the screen.
    /// It continues looping until a quit event is received, at which point it returns control to the caller.
    VelECSEngine& Run();

    /// \brief Shuts down the engine, releasing any resources acquired during initialization or runtime.
    /// \return Reference to the VelECSEngine instance, allowing for method chaining.
    ///
    /// This method is responsible for cleaning up and releasing any resources to ensure a clean exit.
    /// It should be called before exiting the program to ensure memory and other resources are properly released.
    VelECSEngine& Cleanup();

    struct SDL_Window* GetWindow();

protected:
    // Protected Fields

    // Protected Methods

private:
    // Private Fields

    // std::unique_ptr<IInput> input;
    std::unique_ptr<IECSManager> ecsManager;

    bool _isInitialized{false}; /// \brief Indicates whether the engine has been initialized.
    bool isQuitting = false; /// \brief Flag to indicate when the application is requesting a shutdown.
    SDL_Event event{NULL}; /// \brief Event structure for handling SDL events.

    struct SDL_Window* _window{nullptr}; /// \brief Pointer to the SDL window structure.

    // Constructors and Destructors
    VelECSEngine() = default;
    ~VelECSEngine() = default;

    // Private Methods

    /// \brief Processes input events.
    ///
    /// This method is called during the main event loop to process SDL2 input events.
    void InputUpdate();

    /// \brief Draws a frame to the screen.
    ///
    /// This method performs the rendering operations required to draw a frame to the screen.
    /// It is called repeatedly during the main event loop.
    void Draw(const float deltaTime);
};

} // namespace velecs
