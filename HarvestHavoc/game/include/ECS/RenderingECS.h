/// \file    RenderingSystems.h
/// \author  Matthew Green
/// \date    10/31/2023 12:32:09
/// 
/// \section LICENSE
/// 
/// Copyright (c) 2023 Matthew Green - All rights reserved
/// Unauthorized copying of this file, via any medium is strictly prohibited
/// Proprietary and confidential

#pragma once

#include "ECS/IRenderingECS.h"

#include "Engine/DeletionQueue.h"

#include <vulkan/vulkan_core.h>

#include <SDL2/SDL.h>

#include <vector>
#include <memory>

namespace hh {

/// \class RenderingSystems
/// \brief Brief description.
///
/// Rest of description.
class RenderingECS : public IRenderingECS {
public:
    // Enums

    // Public Fields

    // Constructors and Destructors

    RenderingECS(flecs::world& ecs, ECSPipelineStages& stages, engine::VulkanEngine& engine);
    
    /// \brief Default deconstructor.
    ~RenderingECS() = default;

    // Public Methods

    /// \brief Shuts down the engine, releasing any resources acquired during initialization or runtime.
    ///
    /// This method is responsible for cleaning up and releasing any resources to ensure a clean exit.
    /// It should be called before exiting the program to ensure memory and other resources are properly released.
    void Cleanup();

    void Init() override;

protected:
    // Protected Fields

    // Protected Methods

    void InitComponents() override;
    void InitSystems() override;
    void InitEntities() override;

private:
    // Private Fields

    ECSPipelineStages& stages;

    VkInstance _instance{nullptr}; /// \brief Handle to the Vulkan library.
    VkDebugUtilsMessengerEXT _debug_messenger{nullptr}; /// \brief Handle for Vulkan debug messaging.
    VkPhysicalDevice _chosenGPU{nullptr}; /// \brief The chosen GPU for rendering operations.
    VkDevice _device{nullptr}; /// \brief Handle to the Vulkan device.
    VkSurfaceKHR _surface{nullptr}; /// \brief Handle to the Vulkan window surface.

    VkSwapchainKHR _swapchain{nullptr}; /// \brief Handle to the Vulkan swapchain.
    VkFormat _swapchainImageFormat{VK_FORMAT_UNDEFINED}; /// \brief The format used for swapchain images.
    std::vector<VkImage> _swapchainImages; /// \brief List of images within the swapchain.
    std::vector<VkImageView> _swapchainImageViews; /// \brief List of image views for accessing swapchain images.
    uint32_t swapchainImageIndex;

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

    size_t renderPipelineIndex{4};

    engine::DeletionQueue _mainDeletionQueue;

    VmaAllocator _allocator{nullptr};

    VkPipelineLayout _meshPipelineLayout{nullptr};
    VkPipeline _meshPipeline{nullptr};
    Mesh _triangleMesh;

    Mesh _monkeyMesh;

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

    void LoadMeshes();

    void UploadMesh(Mesh& mesh);

    flecs::entity CreatePerspectiveCamera(const engine::Vec3 position = engine::Vec3::ZERO,
        const engine::Vec3 rotation = engine::Vec3::ZERO,
        const engine::Vec2 resolution = engine::Vec2{1920.0f, 1080.0f},
        const float verticalFOV = 70.0f,
        const float aspectRatio = 16.0f/9.0f,
        const float nearPlaneOffset = 0.1f,
        const float farPlaneOffset = 200.0f);

    glm::mat4 GetRenderMatrix(const Transform& transform, const flecs::entity camera);
};

} // namespace hh
