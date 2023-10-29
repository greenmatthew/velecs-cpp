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

#include "Engine/DeletionQueue.h"

#include "Graphics/Mesh.h"
#include "Graphics/MeshPushConstants.h"

#include "Input/IInput.h"

#include <vulkan/vulkan_core.h>

#include <SDL2/SDL.h>

#include <vector>
#include <memory>

namespace engine {

class Entity;

/// \class VulkanEngine
/// \brief Brief description.
///
/// Rest of description.
class VulkanEngine {
public:
    // Enums

    // Public Fields

    // Delete the copy constructor and assignment operator to prevent copies
    VulkanEngine(const VulkanEngine&) = delete;
    VulkanEngine& operator=(const VulkanEngine&) = delete;
    
    // Public Methods

    /// \brief Provide a static method to access the singleton instance
    static VulkanEngine& GetInstance() {
        static VulkanEngine instance;  // Guaranteed to be destroyed, instantiated on first use.
        return instance;
    }

    /// \brief Initializes the engine, setting up necessary Vulkan objects and other resources.
    ///
    /// This method sets up Vulkan, SDL2, and other critical structures required for rendering and processing.
    /// It should be called before attempting to use any other methods of this class.
    void Init();

    /// \brief Initializes input handling.
    ///
    /// This method sets up SDL2 event handling for processing user input.
    /// It is called by the Init method during engine initialization.
    void InitInput(IInput * const inputHandle);

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

    void SwapToNextRenderPipeline();

    void TrackEntity(std::shared_ptr<Entity> entity);

protected:
    // Protected Fields

    // Protected Methods

private:
    // Private Fields

    bool _isInitialized{false}; /// \brief Indicates whether the engine has been initialized.
    int _frameNumber{0}; /// \brief Keeps track of the current frame number.
    bool isQuitting = false; /// \brief Flag to indicate when the application is requesting a shutdown.
    SDL_Event event{NULL}; /// \brief Event structure for handling SDL events.
    
    VkExtent2D _windowExtent{1700, 900}; /// \brief Desired dimensions of the rendering window.

    struct SDL_Window* _window{nullptr}; /// \brief Pointer to the SDL window structure.

    IInput* inputHandle{nullptr};

    VkInstance _instance{nullptr}; /// \brief Handle to the Vulkan library.
    VkDebugUtilsMessengerEXT _debug_messenger{nullptr}; /// \brief Handle for Vulkan debug messaging.
    VkPhysicalDevice _chosenGPU{nullptr}; /// \brief The chosen GPU for rendering operations.
    VkDevice _device{nullptr}; /// \brief Handle to the Vulkan device.
    VkSurfaceKHR _surface{nullptr}; /// \brief Handle to the Vulkan window surface.

    VkSwapchainKHR _swapchain{nullptr}; /// \brief Handle to the Vulkan swapchain.
    VkFormat _swapchainImageFormat{VK_FORMAT_UNDEFINED}; /// \brief The format used for swapchain images.
    std::vector<VkImage> _swapchainImages; /// \brief List of images within the swapchain.
    std::vector<VkImageView> _swapchainImageViews; /// \brief List of image views for accessing swapchain images.

    VkQueue _graphicsQueue{nullptr}; /// \brief Queue used for submitting graphics commands.
    uint32_t _graphicsQueueFamily{0}; /// \brief Index of the queue family for graphics operations.
    VkCommandPool _commandPool{nullptr}; /// \brief Pool for allocating command buffers.
    VkCommandBuffer _mainCommandBuffer{nullptr}; /// \brief Main command buffer for recording rendering commands.

    VkRenderPass _renderPass{nullptr}; /// \brief Handle to the Vulkan render pass.
    std::vector<VkFramebuffer> _framebuffers; /// \brief List of framebuffers for rendering.

    VkSemaphore _presentSemaphore{nullptr}, _renderSemaphore{nullptr}; /// \brief Semaphore for synchronizing image presentation.
    VkFence _renderFence{nullptr}; /// \brief Fence for synchronizing rendering operations.

    VkPipelineLayout _trianglePipelineLayout{nullptr}; /// \brief Handle to the pipeline layout.
    VkPipeline _trianglePipeline{nullptr}; /// \brief Handle to the pipeline.
    VkPipeline _redTrianglePipeline{nullptr}; /// \brief Handle to the pipeline.
    VkPipeline _triangleWireFramePipeline{nullptr}; /// \brief Handle to the pipeline.
    VkPipeline _rainbowTrianglePipeline{nullptr}; /// \brief Handle to the pipeline.

    size_t renderPipelineIndex{0};

    DeletionQueue _mainDeletionQueue;

    VmaAllocator _allocator{nullptr};

    VkPipelineLayout _meshPipelineLayout{nullptr};
    VkPipeline _meshPipeline{nullptr};
    Mesh _triangleMesh;

    Mesh _monkeyMesh;

    std::vector<std::shared_ptr<Entity>> entities;

    // Constructors and Destructors
    VulkanEngine() = default;
    ~VulkanEngine() = default;

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

    /// \brief Processes input events.
    ///
    /// This method is called during the main event loop to process SDL2 input events.
    void InputUpdate();

    /// \brief Draws a frame to the screen.
    ///
    /// This method performs the rendering operations required to draw a frame to the screen.
    /// It is called repeatedly during the main event loop.
    void Draw();

    void LoadMeshes();

    void UploadMesh(Mesh& mesh);
};

} // namespace engine
