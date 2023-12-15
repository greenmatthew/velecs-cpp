/// @file    RenderingECSModule.h
/// @author  Matthew Green
/// @date    2023-11-13 18:02:54
/// 
/// @section LICENSE
/// 
/// Copyright (c) 2023 Matthew Green - All rights reserved
/// Unauthorized copying of this file, via any medium is strictly prohibited
/// Proprietary and confidential

#pragma once

#include "velecs/ECS/Modules/IECSModule.h"

#include "velecs/Memory/DeletionQueue.h"
#include "velecs/Math/Vec2.h"
#include "velecs/Math/Vec3.h"

#include "velecs/ECS/Components/Rendering/Transform.h"
#include "velecs/ECS/Components/Rendering/Mesh.h"
#include "velecs/ECS/Components/Rendering/SimpleMesh.h"
#include "velecs/ECS/Components/Rendering/Material.h"
#include "velecs/ECS/Components/Rendering/PerspectiveCamera.h"
#include "velecs/ECS/Components/Rendering/OrthoCamera.h"
#include "velecs/ECS/Components/Rendering/MainCamera.h"

#include <vulkan/vulkan.h>

#include <vma/vk_mem_alloc.h>

#include <VkBootstrap.h>

#include <vector>

struct SDL_Window;

namespace velecs {

/// @struct RenderingECSModule
/// @brief Brief description.
///
/// Rest of description.
struct RenderingECSModule : public IECSModule<RenderingECSModule> {
public:
    // Enums

    // Public Fields

    // Constructors and Destructors

    /// @brief Constructor.
    RenderingECSModule(flecs::world& ecs);

    /// @brief Deconstructor.
    ~RenderingECSModule();

    // Public Methods

    void OnWindowMinimize() const;

    void OnWindowResize();

    static flecs::entity CreatePerspectiveCamera
    (
        flecs::world& ecs,
        const Vec3 position = Vec3::ZERO,
        const Vec3 rotation = Vec3::ZERO,
        const float aspectRatio = 16.0f/9.0f,
        const float verticalFOV = 70.0f,
        const float nearPlaneOffset = 0.1f,
        const float farPlaneOffset = 200.0f
    );
    
    static flecs::entity CreateOrthoCamera
    (
        flecs::world& ecs,
        const Vec3 position,
        const Vec3 rotation,
        const Rect extent,
        const float nearPlaneOffset = 0.1f,
        const float farPlaneOffset = 200.0f
    );

    static flecs::entity GetMainCameraEntity(flecs::world& ecs);

    const Rect RenderingECSModule::GetWindowExtent() const;

protected:
    // Protected Fields

    // Protected Methods

private:
    // Private Fields

    int _frameNumber{0}; /// @brief Keeps track of the current frame number.

    bool shouldRender{true};

    SDL_Window* _window{nullptr}; /// @brief Pointer to the SDL window structure.

    VkExtent2D windowExtent{1700, 900}; /// @brief Desired dimensions of the rendering window.

    VkInstance _instance{VK_NULL_HANDLE}; /// @brief Handle to the Vulkan library.
    VkDebugUtilsMessengerEXT _debug_messenger{VK_NULL_HANDLE}; /// @brief Handle for Vulkan debug messaging.
    VkPhysicalDevice _chosenGPU{VK_NULL_HANDLE}; /// @brief The chosen GPU for rendering operations.
    VkDevice _device{VK_NULL_HANDLE}; /// @brief Handle to the Vulkan device.
    VkSurfaceKHR _surface{VK_NULL_HANDLE}; /// @brief Handle to the Vulkan window surface.

    VkSwapchainKHR _swapchain{VK_NULL_HANDLE}; /// @brief Handle to the Vulkan swapchain.
    VkFormat _swapchainImageFormat{VK_FORMAT_UNDEFINED}; /// @brief The format used for swapchain images.
    std::vector<VkImage> _swapchainImages; /// @brief List of images within the swapchain.
    std::vector<VkImageView> _swapchainImageViews; /// @brief List of image views for accessing swapchain images.
    uint32_t swapchainImageIndex{0};

    VkQueue _graphicsQueue{VK_NULL_HANDLE}; /// @brief Queue used for submitting graphics commands.
    uint32_t _graphicsQueueFamily{0}; /// @brief Index of the queue family for graphics operations.
    VkCommandPool _commandPool{VK_NULL_HANDLE}; /// @brief Pool for allocating command buffers.
    VkCommandBuffer _mainCommandBuffer{VK_NULL_HANDLE}; /// @brief Main command buffer for recording rendering commands.

    VkRenderPass _renderPass{VK_NULL_HANDLE}; /// @brief Handle to the Vulkan render pass.
    std::vector<VkFramebuffer> _framebuffers; /// @brief List of framebuffers for rendering.

    VkSemaphore _presentSemaphore{VK_NULL_HANDLE}, _renderSemaphore{VK_NULL_HANDLE}; /// @brief Semaphore for synchronizing image presentation.
    VkFence _renderFence{VK_NULL_HANDLE}; /// @brief Fence for synchronizing rendering operations.

    VkPipeline currentPipeline{VK_NULL_HANDLE};

    VkPipelineLayout _trianglePipelineLayout{VK_NULL_HANDLE}; /// @brief Handle to the pipeline layout.
    VkPipeline _trianglePipeline{VK_NULL_HANDLE}; /// @brief Handle to the pipeline.
    VkPipeline _redTrianglePipeline{VK_NULL_HANDLE}; /// @brief Handle to the pipeline.
    VkPipeline _triangleWireFramePipeline{VK_NULL_HANDLE}; /// @brief Handle to the pipeline.
    VkPipeline _rainbowTrianglePipeline{VK_NULL_HANDLE}; /// @brief Handle to the pipeline.

    size_t renderPipelineIndex{4};

    DeletionQueue _mainDeletionQueue;

    VmaAllocator _allocator{nullptr};

    VkPipelineLayout _meshPipelineLayout{VK_NULL_HANDLE};
    VkPipeline _meshPipeline{VK_NULL_HANDLE};
    Mesh _triangleMesh;

    Mesh _monkeyMesh;

    SimpleMesh simpleTriangleMesh;
    VkPipelineLayout simpleMeshPipelineLayout{VK_NULL_HANDLE};
    VkPipeline simpleMeshPipeline{VK_NULL_HANDLE};

    // Private Methods

    void InitWindow();

    /// @brief Initializes Vulkan-specific structures, such as the instance, debug messenger, and physical device selection.
    ///
    /// This method encapsulates the setup of critical Vulkan structures required for rendering.
    /// It is called by the Init method during engine initialization.
    void InitVulkan();

    /// @brief Initializes the swapchain for rendering.
    ///
    /// This method sets up the swapchain which is critical for rendering frames to the screen.
    /// It is called by the Init method during engine initialization.
    void InitSwapchain();

    void RebuildSwapchain();

    /// @brief Initializes command buffers and pools for rendering.
    ///
    /// This method sets up the command pool and main command buffer used for rendering.
    /// It is called by the Init method during engine initialization.
    void InitCommands();

    /// @brief Initializes the default render pass used for rendering.
    ///
    /// This method sets up the render pass which defines how rendering operations are handled.
    /// It is called by the Init method during engine initialization.
    void InitDefaultRenderPass();

    /// @brief Initializes framebuffers used for rendering.
    ///
    /// This method sets up the framebuffers which hold references to the images used in rendering.
    /// It is called by the Init method during engine initialization.
    void InitFrameBuffers();

    /// @brief Initializes synchronization structures used for rendering.
    ///
    /// This method sets up semaphores and fences used to synchronize rendering operations.
    /// It is called by the Init method during engine initialization.
    void InitSyncStructures();

    /// @brief Initializes the rendering pipelines by loading shader modules.
    ///
    /// This method loads the shader modules necessary for rendering, including a vertex shader and a fragment shader for rendering triangles.
    /// It leverages the load_shader_module method to load SPIR-V compiled shaders from file, and reports any errors encountered during the loading process.
    void InitPipelines();

    /// @brief Initializes the ImGUI user interface.
    ///
    /// This method sets up ImGUI which is used for rendering the user interface.
    /// It is called by the Init method during engine initialization.
    void InitImGUI();

    void PreDrawStep(float deltaTime);

    void PostDrawStep(float deltaTime);

    void BindPipeline(const Material& material);

    void Draw
    (
        const float deltaTime,
        const glm::mat4 renderMatrix,
        const SimpleMesh& mesh,
        const Material& material
    );

    template<typename TMesh>
    void UploadMesh(TMesh& mesh);

    void DisplayFPSCounter() const;
};

} // namespace velecs
