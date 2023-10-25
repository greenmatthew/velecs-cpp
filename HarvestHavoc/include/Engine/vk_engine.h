/// \file    vk_engine.h
/// \author  Matthew Green
/// \date    10/19/2023 14:58:06
/// 
/// \section LICENSE
/// 
/// Copyright (c) 2023 Matthew Green - All rights reserved
/// Unauthorized copying of this file, via any medium is strictly prohibited
/// Proprietary and confidential

#pragma once

#include <Engine/vk_types.h>

#include <vector>

#include <SDL2/SDL.h>

namespace HarvestHavoc::Engine {

/// \class VulkanEngine
/// \brief Brief description.
///
/// Rest of description.
class VulkanEngine {
public:
    // Enums

    // Public Fields

    // Constructors and Destructors
    
    // Public Methods

    /// \brief Initializes the engine, setting up necessary Vulkan objects and other resources.
    ///
    /// This method sets up Vulkan, SDL2, and other critical structures required for rendering and processing.
    /// It should be called before attempting to use any other methods of this class.
    void Init();

    /// \brief Shuts down the engine, releasing any resources acquired during initialization or runtime.
    ///
    /// This method is responsible for cleaning up and releasing any resources to ensure a clean exit.
    /// It should be called before exiting the program to ensure memory and other resources are properly released.
    void Cleanup();

    /// \brief Runs the main event and rendering loop, handling input and drawing frames.
    ///
    /// This method enters a loop which processes SDL2 events, updates the engine state, and renders frames to the screen.
    /// It continues looping until a quit event is received, at which point it returns control to the caller.
    void Run();

protected:
    // Protected Fields

    // Protected Methods

private:
    // Private Fields

    bool _isInitialized{false}; /// \brief Indicates whether the engine has been initialized.
    int _frameNumber{0}; /// \brief Keeps track of the current frame number.
    bool isQuitting = false; /// \brief Flag to indicate when the application is requesting a shutdown.
    SDL_Event event; /// \brief Event structure for handling SDL events.
    
    VkExtent2D _windowExtent{1700, 900}; /// \brief Desired dimensions of the rendering window.

    struct SDL_Window* _window{nullptr}; /// \brief Pointer to the SDL window structure.

    VkInstance _instance; /// \brief Handle to the Vulkan library.
    VkDebugUtilsMessengerEXT _debug_messenger; /// \brief Handle for Vulkan debug messaging.
    VkPhysicalDevice _chosenGPU; /// \brief The chosen GPU for rendering operations.
    VkDevice _device; /// \brief Handle to the Vulkan device.
    VkSurfaceKHR _surface; /// \brief Handle to the Vulkan window surface.

    VkSwapchainKHR _swapchain; /// \brief Handle to the Vulkan swapchain.
    VkFormat _swapchainImageFormat; /// \brief The format used for swapchain images.
    std::vector<VkImage> _swapchainImages; /// \brief List of images within the swapchain.
    std::vector<VkImageView> _swapchainImageViews; /// \brief List of image views for accessing swapchain images.

    VkQueue _graphicsQueue; /// \brief Queue used for submitting graphics commands.
    uint32_t _graphicsQueueFamily; /// \brief Index of the queue family for graphics operations.
    VkCommandPool _commandPool; /// \brief Pool for allocating command buffers.
    VkCommandBuffer _mainCommandBuffer; /// \brief Main command buffer for recording rendering commands.

    VkRenderPass _renderPass; /// \brief Handle to the Vulkan render pass.
    std::vector<VkFramebuffer> _framebuffers; /// \brief List of framebuffers for rendering.

    VkSemaphore _presentSemaphore, _renderSemaphore; /// \brief Semaphore for synchronizing image presentation.
    VkFence _renderFence; /// \brief Fence for synchronizing rendering operations.

    VkPipelineLayout _trianglePipelineLayout; /// \brief Handle to the pipeline layout.
    VkPipeline _trianglePipeline; /// \brief Handle to the pipeline.

    // Private Methods

    /// \brief Initializes Vulkan-specific structures, such as the instance, debug messenger, and physical device selection.
    ///
    /// This method encapsulates the setup of critical Vulkan structures required for rendering.
    /// It is called by the Init method during engine initialization.
    void InitVulkan();

    /// \brief Initializes the swapchain for rendering.
    ///
    /// This method sets up the swapchain which is critical for rendering frames to the screen.
    /// It is called by the Init method during engine initialization.
    void InitSwapchain();

    /// \brief Initializes command buffers and pools for rendering.
    ///
    /// This method sets up the command pool and main command buffer used for rendering.
    /// It is called by the Init method during engine initialization.
    void InitCommands();

    /// \brief Initializes the default render pass used for rendering.
    ///
    /// This method sets up the render pass which defines how rendering operations are handled.
    /// It is called by the Init method during engine initialization.
    void InitDefaultRenderPass();

    /// \brief Initializes framebuffers used for rendering.
    ///
    /// This method sets up the framebuffers which hold references to the images used in rendering.
    /// It is called by the Init method during engine initialization.
    void InitFrameBuffers();

    /// \brief Initializes synchronization structures used for rendering.
    ///
    /// This method sets up semaphores and fences used to synchronize rendering operations.
    /// It is called by the Init method during engine initialization.
    void InitSyncStructures();


    /// \brief Initializes the rendering pipelines by loading shader modules.
    ///
    /// This method loads the shader modules necessary for rendering, including a vertex shader and a fragment shader for rendering triangles.
    /// It leverages the load_shader_module method to load SPIR-V compiled shaders from file, and reports any errors encountered during the loading process.
    void InitPipelines();

    /// \brief Initializes the ImGUI user interface.
    ///
    /// This method sets up ImGUI which is used for rendering the user interface.
    /// It is called by the Init method during engine initialization.
    void InitImGUI();

    /// \brief Initializes input handling.
    ///
    /// This method sets up SDL2 event handling for processing user input.
    /// It is called by the Init method during engine initialization.
    void InitInput();

    /// \brief Processes input events.
    ///
    /// This method is called during the main event loop to process SDL2 input events.
    void InputUpdate();

    /// \brief Draws a frame to the screen.
    ///
    /// This method performs the rendering operations required to draw a frame to the screen.
    /// It is called repeatedly during the main event loop.
    void Draw();

    /// \brief Loads a shader module from a SPIR-V file.
    ///
    /// \param filePath The path to the SPIR-V file.
    /// \param outShaderModule A pointer to a VkShaderModule structure where the loaded shader module will be stored.
    /// \return Returns true if the shader module was loaded successfully, false otherwise.
    ///
    /// This method reads a SPIR-V file from disk, creates a Vulkan shader module from the contents, 
    /// and stores the shader module in the provided VkShaderModule structure.
    bool LoadShaderModule(const char* filePath, VkShaderModule* outShaderModule);

    bool LoadVertShaderModule(const char* vertFilePath, VkShaderModule* outVertShaderModule);
    bool LoadFragShaderModule(const char* fragFilePath, VkShaderModule* outFragShaderModule);
};

} // namespace HarvestHavoc::Engine
