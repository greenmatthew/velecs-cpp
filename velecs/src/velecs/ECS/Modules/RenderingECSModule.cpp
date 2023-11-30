/// @file    RenderingECSModule.cpp
/// @author  Matthew Green
/// @date    2023-11-13 18:02:26
/// 
/// @section LICENSE
/// 
/// Copyright (c) 2023 Matthew Green - All rights reserved
/// Unauthorized copying of this file, via any medium is strictly prohibited
/// Proprietary and confidential

#include "velecs/ECS/Modules/RenderingECSModule.h"

#include "velecs/ECS/Modules/PhysicsECSModule.h"
#include "velecs/ECS/Modules/InputECSModule.h"

#include "velecs/VelECSEngine.h"

#include "velecs/Memory/AllocatedBuffer.h"
#include "velecs/Engine/vk_initializers.h"
#include "velecs/Rendering/ShaderModule.h"
#include "velecs/Rendering/PipelineBuilder.h"
#include "velecs/Rendering/MeshPushConstants.h"
#include "velecs/Graphics/Color32.h"
#include "velecs/FileManagement/Path.h"

#include <iostream>
#include <fstream>
#include <chrono>

#include <SDL2/SDL.h>
#include <SDL2/SDL_vulkan.h>

#include <VkBootstrap.h>

#define VMA_IMPLEMENTATION
#include <vma/vk_mem_alloc.h>

#include <glm/gtc/matrix_transform.hpp>

#include <imgui.h>
#include <backends/imgui_impl_sdl2.h>
#include <backends/imgui_impl_vulkan.h>

#define VK_CHECK(x)                                                    \
    do                                                                 \
    {                                                                  \
        VkResult err = x;                                              \
        if (err)                                                       \
        {                                                              \
            std::cout <<"Detected Vulkan error: " << err << std::endl; \
            abort();                                                   \
        }                                                              \
    } while (0)

namespace velecs {

// Public Fields

// Constructors and Destructors

RenderingECSModule::RenderingECSModule(flecs::world& ecs)
    : IECSModule(ecs)
{
    ecs.import<PhysicsECSModule>();
    ecs.import<InputECSModule>();

    InitWindow();

    InitVulkan();
    InitSwapchain();
    InitCommands();
    InitDefaultRenderPass();
    InitFrameBuffers();
    InitSyncStructures();
    InitPipelines();

    InitImGUI();

    ecs.component<Transform>();
    ecs.component<Mesh>();
    ecs.component<SimpleMesh>();
    ecs.component<Material>();

    flecs::entity entityPrefab = CommonECSModule::GetPrefab(ecs, "CommonECSModule::PR_Entity");
    flecs::entity renderPrefab = ecs.prefab("PR_Render")
        .is_a(entityPrefab)
        .add<SimpleMesh>()
        .set<Material>({Color32::MAGENTA, simpleMeshPipeline, simpleMeshPipelineLayout})
        ;

    flecs::entity triangleRenderPrefab = ecs.prefab("PR_TriangleRender")
        .is_a(renderPrefab)
        .set<SimpleMesh>({ SimpleMesh::EQUILATERAL_TRIANGLE() })
        ;
    
    flecs::entity squareRenderPrefab = ecs.prefab("PR_SquareRender")
        .is_a(renderPrefab)
        .set<SimpleMesh>({ SimpleMesh::SQUARE() })
        ;
    
    ecs.system()
        .kind(stages->PreDraw)
        .iter([this](flecs::iter& it)
        {
            float deltaTime = it.delta_time();
            PreDrawStep(deltaTime);
        }
    );

    ecs.system()
        .kind(stages->PostDraw)
        .iter([this](flecs::iter& it)
        {
            float deltaTime = it.delta_time();
            PostDrawStep(deltaTime);
        }
    );

    ecs.system()
        .kind(stages->Draw)
        .iter([this](flecs::iter& it)
            {
                ImGui::ShowDemoWindow(); // Show demo window! :)

                static float f = 0.0f;
                static int counter = 0;
                static ImGuiIO& io = ImGui::GetIO(); (void)io;

                // Set window flags
                ImGuiWindowFlags window_flags =
                    ImGuiWindowFlags_NoDecoration |
                    ImGuiWindowFlags_AlwaysAutoResize |
                    ImGuiWindowFlags_NoSavedSettings |
                    ImGuiWindowFlags_NoFocusOnAppearing |
                    ImGuiWindowFlags_NoNav
                    ;
                
                // Calculate the top-right position for the FPS counter
                ImVec2 window_pos = ImVec2(io.DisplaySize.x - 10.0f, 10.0f); // 10 pixels from the top-right corner
                ImVec2 window_pos_pivot = ImVec2(1.0f, 0.0f); // Pivot at the top-right corner of the window
                ImGui::SetNextWindowPos(window_pos, ImGuiCond_Always, window_pos_pivot);

                // Begin the window with the specified flags
                ImGui::Begin("FPS Counter", nullptr, window_flags);

                // Display FPS
                ImGui::Text("FPS: %.1f", io.Framerate);
                ImGui::Text("ms/frame: %.3f", 1000.0f / io.Framerate);

                // End the window
                ImGui::End();

                ImGui::Begin("Hello, world!");                          // Create a window called "Hello, world!" and append into it.

                ImGui::Text("This is some useful text.");               // Display some text (you can use a format strings too)

                ImGui::SliderFloat("float", &f, 0.0f, 1.0f);            // Edit 1 float using a slider from 0.0f to 1.0f

                if (ImGui::Button("Button"))                            // Buttons return true when clicked (most widgets return true when edited/activated)
                    counter++;
                ImGui::SameLine();
                ImGui::Text("counter = %d", counter);

                ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / io.Framerate, io.Framerate);
                ImGui::End();
            }
        );

    // ecs.system<Transform, Mesh, Material>()
    //     .kind(stages->Draw)
    //     .iter([this](flecs::iter& it, Transform* transforms, Mesh* meshes, Material* materials)
    //     {
    //         float deltaTime = it.delta_time();

    //         const auto mainCameraEntity = it.world().singleton<MainCamera>();
    //         const auto cameraEntity = mainCameraEntity.get<MainCamera>()->camera;
    //         const auto cameraTransform = cameraEntity.get<Transform>();

    //         for (auto i : it)
    //         {
    //             Transform transform = transforms[i];
    //             Mesh mesh = meshes[i];
    //             Material material = materials[i];
    //             flecs::entity entity = it.entity(i);

    //             if (mesh._vertices.empty() || material.pipeline == VK_NULL_HANDLE || material.pipelineLayout == VK_NULL_HANDLE)
    //             {
    //                 continue; // Not enough data to render? Skip entity
    //             }

    //             if (cameraEntity.has<PerspectiveCamera>())
    //             {
    //                 const auto perspectiveCamera = cameraEntity.get<PerspectiveCamera>();
    //                 Draw(deltaTime, cameraEntity, perspectiveCamera, cameraTransform, entity, transform, mesh, material);
    //             }
    //             else if (cameraEntity.has<OrthoCamera>())
    //             {
    //                 const auto orthoCamera = cameraEntity.get<OrthoCamera>();
    //                 Draw(deltaTime, cameraEntity, orthoCamera, cameraTransform, entity, transform, mesh, material);
    //             }
    //             else
    //             {
    //                 std::exception("MainCamera singleton is missing a PerspectiveCamera or OrthoCamera component.");
    //             }
    //         }
    //     }
    // );

    ecs.system<Transform, SimpleMesh, Material>()
        .kind(stages->Draw)
        .iter([this](flecs::iter& it, Transform* transforms, SimpleMesh* meshes, Material* materials)
        {
            float deltaTime = it.delta_time();

            const auto mainCameraEntity = it.world().singleton<MainCamera>();
            const auto cameraEntity = mainCameraEntity.get<MainCamera>()->camera;
            const auto cameraTransform = cameraEntity.get<Transform>();

            const PerspectiveCamera* perspectiveCamera;
            const OrthoCamera* orthoCamera;
            bool usingPerspective = true;

            if (cameraEntity.has<PerspectiveCamera>())
            {
                perspectiveCamera = cameraEntity.get<PerspectiveCamera>();
                usingPerspective = true;
            }
            else if (cameraEntity.has<OrthoCamera>())
            {
                orthoCamera = cameraEntity.get<OrthoCamera>();
                usingPerspective = false;
            }
            else
            {
                throw std::runtime_error("MainCamera singleton is missing a PerspectiveCamera or OrthoCamera component.");
            }

            for (auto i : it)
            {
                const Transform& transform = transforms[i];
                SimpleMesh& mesh = meshes[i];
                const Material& material = materials[i];
                const flecs::entity entity = it.entity(i);

                if (mesh._vertices.empty() || material.pipeline == VK_NULL_HANDLE || material.pipelineLayout == VK_NULL_HANDLE)
                {
                    continue; // Not enough data to render? Skip entity
                }

                if (!mesh._vertexBuffer.IsInitialized())
                {
                    UploadMesh(mesh);
                }

                if (usingPerspective)
                {
                    const glm::mat4 renderMatrix = transform.GetRenderMatrix(cameraTransform, perspectiveCamera);
                    Draw(deltaTime, renderMatrix, mesh, material);
                }
                else
                {
                    const auto orthoCamera = cameraEntity.get<OrthoCamera>();
                    // Draw(deltaTime, cameraEntity, orthoCamera, cameraTransform, entity, transform, mesh, material);
                }
            }
        }
    );

    ecs.system()
        .kind(stages->Update)
        .iter([this](flecs::iter& it)
        {
            flecs::world ecs = it.world();

            flecs::entity inputEntity = ecs.singleton<Input>();
            const Input* const input = inputEntity.get<Input>();

            if (input->IsPressed(SDLK_F11))
            {
                Uint32 toggle = SDL_GetWindowFlags(_window) & SDL_WINDOW_FULLSCREEN;
                SDL_SetWindowFullscreen(_window, toggle ? 0 : SDL_WINDOW_FULLSCREEN_DESKTOP);
            }
        }
    );
}

RenderingECSModule::~RenderingECSModule()
{
    // make sure the GPU has stopped doing its things
    vkWaitForFences(_device, 1, &_renderFence, true, 1000000000);

    ImGui_ImplVulkan_Shutdown();
    ImGui_ImplSDL2_Shutdown();
    ImGui::DestroyContext();

    _mainDeletionQueue.Flush();

    const size_t swapchain_imagecount = _swapchainImages.size();
    for (int i = 0; i < swapchain_imagecount; i++)
    {
        vkDestroyFramebuffer(_device, _framebuffers[i], nullptr);
        vkDestroyImageView(_device, _swapchainImageViews[i], nullptr);
    }
    _swapchainImageViews.clear();
    _framebuffers.clear();

    vkDestroyRenderPass(_device, _renderPass, nullptr);
    vkDestroyCommandPool(_device, _commandPool, nullptr);
    vkDestroySwapchainKHR(_device, _swapchain, nullptr);

    vmaDestroyAllocator(_allocator);
    vkDestroyDevice(_device, nullptr);
    vkDestroySurfaceKHR(_instance, _surface, nullptr);
    vkb::destroy_debug_utils_messenger(_instance, _debug_messenger);
    vkDestroyInstance(_instance, nullptr);
    SDL_DestroyWindow(_window);
}

void RenderingECSModule::OnWindowMinimize() const
{
    while (true)
    {
        // Poll for events to keep the application responsive
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
                case SDL_QUIT:
                    exit(0);
                case SDL_WINDOWEVENT:
                    if (event.window.event == SDL_WINDOWEVENT_RESTORED)
                    {
                        return;
                    }
                    break;
                default:
                    break;
            }
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
}

void RenderingECSModule::OnWindowResize()
{
    int width, height;
    SDL_GetWindowSize(_window, &width, &height);
    while (width == 0 || height == 0)
    {
        // Poll for events to keep the application responsive
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                exit(0); // Or handle the quit event appropriately
            }
            // Handle other necessary events
        }

        // Recheck the window size
        SDL_GetWindowSize(_window, &width, &height);
        std::cout << "window: " << "(" << width << ", " << height << ")" << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }

    vkDeviceWaitIdle(_device);

    windowExtent.width = width;
    windowExtent.height = height;
    

    flecs::world& world = ecs();
    Camera& cam = GetMainCamera(world);
    cam.SetResolution(Vec2{(float)width, (float)height});

    for (auto imageView : _swapchainImageViews)
    {
        vkDestroyImageView(_device, imageView, nullptr);
    }
    _swapchainImageViews.clear(); // Clear the list after destroying the image views

    if (_swapchain != VK_NULL_HANDLE)
    {
        vkDestroySwapchainKHR(_device, _swapchain, nullptr);
        _swapchain = VK_NULL_HANDLE; // Reset the swapchain handle
    }

    for (auto framebuffer : _framebuffers)
    {
        vkDestroyFramebuffer(_device, framebuffer, nullptr);
    }
    _framebuffers.clear();

    InitSwapchain();
    InitFrameBuffers();
}

// Public Methods

flecs::entity RenderingECSModule::CreatePerspectiveCamera(flecs::world& ecs,
    const Vec3 position /*= Vec3::ZERO*/,
    const Vec3 rotation /*= Vec3::ZERO*/,
    const Vec2 resolution /*= Vec2{1920.0f, 1080.0f}*/,
    const float verticalFOV /*= 70.0f*/,
    const float nearPlaneOffset /*= 0.1f*/,
    const float farPlaneOffset /*= 200.0f*/)
{
    flecs::entity camEntity = ecs.entity("Camera")
        .override<Transform>()
        .set_override<PerspectiveCamera>({resolution, verticalFOV, nearPlaneOffset, farPlaneOffset});
    
    camEntity.set<Transform>({camEntity, position, rotation});

    return camEntity;
}

flecs::entity RenderingECSModule::CreateOrthoCamera(flecs::world& ecs,
    const Vec3 position /*= Vec3::ZERO*/,
    const Vec3 rotation /*= Vec3::ZERO*/,
    const Vec2 resolution /*= Vec2{1920.0f, 1080.0f}*/,
    const float nearPlaneOffset /*= 0.1f*/,
    const float farPlaneOffset /*= 200.0f*/)
{
    flecs::entity camEntity = ecs.entity("Camera")
        .override<Transform>()
        .set_override<OrthoCamera>({resolution, nearPlaneOffset, farPlaneOffset});

    camEntity.set<Transform>({camEntity, position, rotation});

    return camEntity;
}

Camera& RenderingECSModule::GetMainCamera(flecs::world& ecs)
{
    const MainCamera* const mainCamera = ecs.get<MainCamera>();
    if (mainCamera == nullptr)
    {
        throw std::runtime_error("MainCamera singleton not found.");
    }

    flecs::entity cameraEntity = mainCamera->camera;
    if (cameraEntity == flecs::entity::null())
    {
        throw std::runtime_error("MainCamera's camera entity is null.");
    }

    Camera* cameraPtr = cameraEntity.get_mut<Camera>();
    if (cameraPtr == nullptr)
    {
        throw std::runtime_error("Camera component not found in MainCamera's camera entity.");
    }

    return *cameraPtr;
}

// Protected Fields

// Protected Methods

// Private Fields

// Private Methods

void RenderingECSModule::InitWindow()
{
    // We initialize SDL and create a window with it. 
    SDL_Init(SDL_INIT_VIDEO);

    SDL_WindowFlags window_flags = (SDL_WindowFlags)(SDL_WINDOW_VULKAN | SDL_WINDOW_RESIZABLE);

    _window = SDL_CreateWindow(
        "Harvest Havoc",
        SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,
        1700,
        900,
        window_flags
    );
    if (_window == nullptr)
    {
        std::cerr << "Failed to create window. SDL Error: " << SDL_GetError() << "\n";
        exit(EXIT_FAILURE);
    }

    if (SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        std::cerr << "Failed to initialize SDL. SDL Error: " << SDL_GetError() << "\n";
        exit(EXIT_FAILURE);
    }
}

void RenderingECSModule::InitVulkan()
{
    vkb::InstanceBuilder builder;

    #ifdef DEBUG_MODE
        const bool enableValidationLayers = true;
        std::cout << "[INFO] DEBUG_MODE defined; using Vulkan Validation Layers." << std::endl;
    #else
        const bool enableValidationLayers = false;
    #endif

    auto inst_ret = builder.set_app_name("Harvest Havoc")
            .request_validation_layers(enableValidationLayers)
            .require_api_version(1, 1, 0)
            .use_default_debug_messenger()
            .build();

    // Check if instance creation was successful before proceeding
    if (!inst_ret)
    {
        std::cerr << "Failed to create Vulkan instance. Error: " << inst_ret.error().message() << "\n";
        exit(EXIT_FAILURE);
    }

    // #ifdef DEBUG_MODE
    // // After building the instance, but before creating the device:
    // if (inst_ret)
    // {
    //     std::cout << "Available validation layers:" << std::endl;
    //     uint32_t layerCount;
    //     vkEnumerateInstanceLayerProperties(&layerCount, nullptr);
    //     std::vector<VkLayerProperties> availableLayers(layerCount);
    //     vkEnumerateInstanceLayerProperties(&layerCount, availableLayers.data());
    //     for (const auto& layer : availableLayers)
    //     {
    //         std::cout << "\t" << layer.layerName << std::endl;
    //     }
    // }
    // #endif

    vkb::Instance vkb_inst = inst_ret.value();

    //store the instance
    _instance = vkb_inst.instance;
    //store the debug messenger
    _debug_messenger = vkb_inst.debug_messenger;

    if (_debug_messenger == nullptr)
    {
        std::cout << "Failed to create debug messenger." << std::endl;
    }

    // get the surface of the window we opened with SDL
    if (!SDL_Vulkan_CreateSurface(_window, _instance, &_surface))
    {
        std::cerr << "Failed to create Vulkan surface. SDL Error: " << SDL_GetError() << "\n";
        exit(EXIT_FAILURE);
    }

    //use vkbootstrap to select a GPU.
    //We want a GPU that can write to the SDL surface and supports Vulkan 1.1
    vkb::PhysicalDeviceSelector selector{ vkb_inst };

    // Create a VkPhysicalDeviceFeatures structure and set the fillModeNonSolid feature to VK_TRUE
    VkPhysicalDeviceFeatures desiredFeatures = {};
    desiredFeatures.fillModeNonSolid = VK_TRUE;

    auto phys_ret = selector
        .set_minimum_version(1, 1)
        .set_surface(_surface)
        .set_required_features(desiredFeatures)
        .select();

    // Check if physical device selection was successful before proceeding
    if (!phys_ret)
    {
        std::cerr << "Failed to select Vulkan physical device. Error: " << phys_ret.error().message() << "\n";
        exit(EXIT_FAILURE);
    }
    vkb::PhysicalDevice physicalDevice = phys_ret.value();

    //create the final Vulkan device
    vkb::DeviceBuilder deviceBuilder{ physicalDevice };
    // automatically propagate needed data from instance & physical device
    auto dev_ret = deviceBuilder.build();
    if (!dev_ret)
    {
        std::cerr << "Failed to create Vulkan device. Error: " << dev_ret.error().message() << "\n";
        exit(EXIT_FAILURE);
    }

    vkb::Device vkbDevice = dev_ret.value();

    // Get the VkDevice handle used in the rest of a Vulkan application
    _device = vkbDevice.device;
    _chosenGPU = physicalDevice.physical_device;

    // use vkbootstrap to get a Graphics queue
    _graphicsQueue = vkbDevice.get_queue(vkb::QueueType::graphics).value();
    _graphicsQueueFamily = vkbDevice.get_queue_index(vkb::QueueType::graphics).value();

    //initialize the memory allocator
    VmaAllocatorCreateInfo allocatorInfo = {};
    allocatorInfo.physicalDevice = _chosenGPU;
    allocatorInfo.device = _device;
    allocatorInfo.instance = _instance;
    vmaCreateAllocator(&allocatorInfo, &_allocator);
}

void RenderingECSModule::InitSwapchain()
{
    vkb::SwapchainBuilder swapchainBuilder = vkb::SwapchainBuilder{_chosenGPU, _device, _surface};

    // use this if u need to test the Color32 struct, otherwise the displayed color will be slightly different, probably brighter.
    // VkSurfaceFormatKHR surfaceFormat = {};
    // surfaceFormat.colorSpace = VK_COLOR_SPACE_EXTENDED_SRGB_LINEAR_EXT;
    // surfaceFormat.format = VK_FORMAT_B8G8R8A8_UNORM;

    vkb::Result<vkb::Swapchain> vkbSwapchainRet = swapchainBuilder
        // .set_desired_format(surfaceFormat)
        .use_default_format_selection()
        .build()
        ;
    
    if (!vkbSwapchainRet.has_value())
    {
        std::cout << vkbSwapchainRet.vk_result() << std::endl;
        std::cout << "Cancelled building swapchain" << std::endl;
        return;
    }
    
    vkb::Swapchain vkbSwapchain = vkbSwapchainRet.value();

    vkbSwapchain.extent = windowExtent;
    //use vsync present mode
    vkbSwapchain.present_mode = VK_PRESENT_MODE_FIFO_KHR;

    //store swapchain and its related images
    _swapchain = vkbSwapchain.swapchain;
    _swapchainImages = vkbSwapchain.get_images().value();
    _swapchainImageViews = vkbSwapchain.get_image_views().value();

    _swapchainImageFormat = vkbSwapchain.image_format;
}

void RenderingECSModule::InitCommands()
{
    //create a command pool for commands submitted to the graphics queue.
    //we also want the pool to allow for resetting of individual command buffers
    VkCommandPoolCreateInfo commandPoolInfo = vkinit::command_pool_create_info(_graphicsQueueFamily, VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT);

    VK_CHECK(vkCreateCommandPool(_device, &commandPoolInfo, nullptr, &_commandPool));

    //allocate the default command buffer that we will use for rendering
    VkCommandBufferAllocateInfo cmdAllocInfo = vkinit::command_buffer_allocate_info(_commandPool, 1);

    VK_CHECK(vkAllocateCommandBuffers(_device, &cmdAllocInfo, &_mainCommandBuffer));
}

void RenderingECSModule::InitDefaultRenderPass()
{
    // the renderpass will use this color attachment.
    VkAttachmentDescription color_attachment = {};
    //the attachment will have the format needed by the swapchain
    color_attachment.format = _swapchainImageFormat;
    //1 sample, we won't be doing MSAA
    color_attachment.samples = VK_SAMPLE_COUNT_1_BIT;
    // we Clear when this attachment is loaded
    color_attachment.loadOp = VK_ATTACHMENT_LOAD_OP_CLEAR;
    // we keep the attachment stored when the renderpass ends
    color_attachment.storeOp = VK_ATTACHMENT_STORE_OP_STORE;
    //we don't care about stencil
    color_attachment.stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
    color_attachment.stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;

    //we don't know or care about the starting layout of the attachment
    color_attachment.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;

    //after the renderpass ends, the image has to be on a layout ready for display
    color_attachment.finalLayout = VK_IMAGE_LAYOUT_PRESENT_SRC_KHR;


    VkAttachmentReference color_attachment_ref = {};
    //attachment number will index into the pAttachments array in the parent renderpass itself
    color_attachment_ref.attachment = 0;
    color_attachment_ref.layout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;

    //we are going to create 1 subpass, which is the minimum you can do
    VkSubpassDescription subpass = {};
    subpass.pipelineBindPoint = VK_PIPELINE_BIND_POINT_GRAPHICS;
    subpass.colorAttachmentCount = 1;
    subpass.pColorAttachments = &color_attachment_ref;


    VkRenderPassCreateInfo render_pass_info = {};
    render_pass_info.sType = VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO;

    //connect the color attachment to the info
    render_pass_info.attachmentCount = 1;
    render_pass_info.pAttachments = &color_attachment;
    //connect the subpass to the info
    render_pass_info.subpassCount = 1;
    render_pass_info.pSubpasses = &subpass;

    VK_CHECK(vkCreateRenderPass(_device, &render_pass_info, nullptr, &_renderPass));
}

void RenderingECSModule::InitFrameBuffers()
{
    //create the framebuffers for the swapchain images. This will connect the render-pass to the images for rendering
    VkFramebufferCreateInfo fb_info = {};
    fb_info.sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;
    fb_info.pNext = nullptr;

    fb_info.renderPass = _renderPass;
    fb_info.attachmentCount = 1;
    fb_info.width = windowExtent.width;
    fb_info.height = windowExtent.height;
    fb_info.layers = 1;

    //grab how many images we have in the swapchain
    const size_t swapchain_imagecount = _swapchainImages.size();
    _framebuffers = std::vector<VkFramebuffer>(swapchain_imagecount);

    //create framebuffers for each of the swapchain image views
    for (int i = 0; i < swapchain_imagecount; i++)
    {
        fb_info.pAttachments = &_swapchainImageViews[i];
        VK_CHECK(vkCreateFramebuffer(_device, &fb_info, nullptr, &_framebuffers[i]));
    }
}

void RenderingECSModule::InitSyncStructures()
{
    //we want to create the fence with the Create Signaled flag, so we can wait on it before using it on a GPU command (for the first frame)
    VkFenceCreateInfo fenceCreateInfo = vkinit::fence_create_info(VK_FENCE_CREATE_SIGNALED_BIT);

    VK_CHECK(vkCreateFence(_device, &fenceCreateInfo, nullptr, &_renderFence));

    _mainDeletionQueue.PushDeletor
    (
        [=]()
        {
            vkDestroyFence(_device, _renderFence, nullptr);
        }
    );

    //for the semaphores we don't need any flags
    VkSemaphoreCreateInfo semaphoreCreateInfo = vkinit::semaphore_create_info();

    VK_CHECK(vkCreateSemaphore(_device, &semaphoreCreateInfo, nullptr, &_presentSemaphore));
    VK_CHECK(vkCreateSemaphore(_device, &semaphoreCreateInfo, nullptr, &_renderSemaphore));

    _mainDeletionQueue.PushDeletor
    (
        [=]()
        {
            vkDestroySemaphore(_device, _presentSemaphore, nullptr);
            vkDestroySemaphore(_device, _renderSemaphore, nullptr);
        }
    );
}

void RenderingECSModule::InitPipelines()
{
    //build the pipeline layout that controls the inputs/outputs of the shader
    //we are not using descriptor sets or other systems yet, so no need to use anything other than empty default
    VkPipelineLayoutCreateInfo pipeline_layout_info = vkinit::pipeline_layout_create_info();

    VK_CHECK(vkCreatePipelineLayout(_device, &pipeline_layout_info, nullptr, &_trianglePipelineLayout));


    //build the stage-create-info for both vertex and fragment stages. This lets the pipeline know the shader modules per stage
    PipelineBuilder pipelineBuilder;

    //vertex input controls how to read vertices from vertex buffers. We aren't using it yet
    pipelineBuilder._vertexInputInfo = vkinit::vertex_input_state_create_info();

    //input assembly is the configuration for drawing triangle lists, strips, or individual points.
    //we are just going to draw triangle list
    pipelineBuilder._inputAssembly = vkinit::input_assembly_create_info(VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST);

    //build viewport and scissor from the swapchain extents
    pipelineBuilder._viewport.x = 0.0f;
    pipelineBuilder._viewport.y = 0.0f;
    pipelineBuilder._viewport.width = (float)windowExtent.width;
    pipelineBuilder._viewport.height = (float)windowExtent.height;
    pipelineBuilder._viewport.minDepth = 0.0f;
    pipelineBuilder._viewport.maxDepth = 1.0f;

    pipelineBuilder._scissor.offset = { 0, 0 };
    pipelineBuilder._scissor.extent = windowExtent;

    //configure the rasterizer to draw filled triangles
    pipelineBuilder._rasterizer = vkinit::rasterization_state_create_info(VK_POLYGON_MODE_FILL, VK_CULL_MODE_NONE, VK_FRONT_FACE_COUNTER_CLOCKWISE);

    //we don't use multisampling, so just run the default one
    pipelineBuilder._multisampling = vkinit::multisampling_state_create_info();

    //a single blend attachment with no blending and writing to RGBA
    pipelineBuilder._colorBlendAttachment = vkinit::color_blend_attachment_state();

    //use the triangle layout we created
    pipelineBuilder._pipelineLayout = _trianglePipelineLayout;

    //add the other shaders
    auto rainbowTriangleVertShader = ShaderModule::CreateVertexShaderModule(_device, "RainbowTriangle.vert.spv");
    pipelineBuilder._shaderStages.push_back(vkinit::pipeline_shader_stage_create_info(VK_SHADER_STAGE_VERTEX_BIT, *rainbowTriangleVertShader));
    auto rainbowTriangleFragShader = ShaderModule::CreateFragmentShaderModule(_device, "RainbowTriangle.frag.spv");
    pipelineBuilder._shaderStages.push_back(vkinit::pipeline_shader_stage_create_info(VK_SHADER_STAGE_FRAGMENT_BIT, *rainbowTriangleFragShader));

    _rainbowTrianglePipeline = pipelineBuilder.BuildPipeline(_device, _renderPass);

    //clear the shader stages for the builder
    pipelineBuilder._shaderStages.clear();










    //we start from just the default empty pipeline layout info
    VkPipelineLayoutCreateInfo mesh_pipeline_layout_info = vkinit::pipeline_layout_create_info();

    //setup push constants
    VkPushConstantRange push_constant = {};
    //this push constant range starts at the beginning
    push_constant.offset = 0;
    //this push constant range takes up the size of a MeshPushConstants struct
    push_constant.size = sizeof(MeshPushConstants);
    //this push constant range is accessible only in the vertex shader
    push_constant.stageFlags = VK_SHADER_STAGE_VERTEX_BIT;

    mesh_pipeline_layout_info.pPushConstantRanges = &push_constant;
    mesh_pipeline_layout_info.pushConstantRangeCount = 1;

    VK_CHECK(vkCreatePipelineLayout(_device, &mesh_pipeline_layout_info, nullptr, &_meshPipelineLayout));

    VertexInputAttributeDescriptor vertexDescription = Vertex::GetVertexDescription();

    //connect the pipeline builder vertex input info to the one we get from Vertex
    pipelineBuilder._vertexInputInfo.pVertexAttributeDescriptions = vertexDescription.attributes.data();
    pipelineBuilder._vertexInputInfo.vertexAttributeDescriptionCount = (uint32_t)vertexDescription.attributes.size();

    pipelineBuilder._vertexInputInfo.pVertexBindingDescriptions = vertexDescription.bindings.data();
    pipelineBuilder._vertexInputInfo.vertexBindingDescriptionCount = (uint32_t)vertexDescription.bindings.size();

    //add the other shaders
    const auto meshVertShader = ShaderModule::CreateVertexShaderModule(_device, "TriangleMesh.vert.spv");
    pipelineBuilder._shaderStages.push_back(
        vkinit::pipeline_shader_stage_create_info(VK_SHADER_STAGE_VERTEX_BIT, *meshVertShader));

    //make sure that triangleFragShader is holding the compiled colored_triangle.frag
    const auto meshFragShader = ShaderModule::CreateFragmentShaderModule(_device, "TriangleMesh.frag.spv");
    pipelineBuilder._shaderStages.push_back(
        vkinit::pipeline_shader_stage_create_info(VK_SHADER_STAGE_FRAGMENT_BIT, *meshFragShader));

    pipelineBuilder._pipelineLayout = _meshPipelineLayout;

    //clear the shader stages for the builder
    pipelineBuilder._shaderStages.clear();







    //we start from just the default empty pipeline layout info
    VkPipelineLayoutCreateInfo simple_mesh_pipeline_layout_info = vkinit::pipeline_layout_create_info();

    //setup push constants
    VkPushConstantRange simple_mesh_push_constant = {};
    //this push constant range starts at the beginning
    simple_mesh_push_constant.offset = 0;
    //this push constant range takes up the size of a MeshPushConstants struct
    simple_mesh_push_constant.size = sizeof(MeshPushConstants);
    //this push constant range is accessible only in the vertex shader
    simple_mesh_push_constant.stageFlags = VK_SHADER_STAGE_VERTEX_BIT | VK_SHADER_STAGE_FRAGMENT_BIT;  // Accessible from both stages

    simple_mesh_pipeline_layout_info.pPushConstantRanges = &simple_mesh_push_constant;
    simple_mesh_pipeline_layout_info.pushConstantRangeCount = 1;

    VK_CHECK(vkCreatePipelineLayout(_device, &simple_mesh_pipeline_layout_info, nullptr, &simpleMeshPipelineLayout));

    VertexInputAttributeDescriptor simpleMeshVertexDescription = SimpleVertex::GetVertexDescription();

    //connect the pipeline builder vertex input info to the one we get from Vertex
    pipelineBuilder._vertexInputInfo.pVertexAttributeDescriptions = simpleMeshVertexDescription.attributes.data();
    pipelineBuilder._vertexInputInfo.vertexAttributeDescriptionCount = (uint32_t)simpleMeshVertexDescription.attributes.size();

    pipelineBuilder._vertexInputInfo.pVertexBindingDescriptions = simpleMeshVertexDescription.bindings.data();
    pipelineBuilder._vertexInputInfo.vertexBindingDescriptionCount = (uint32_t)simpleMeshVertexDescription.bindings.size();

    //add the other shaders
    const auto simpleMeshVertShader = ShaderModule::CreateVertexShaderModule(_device, "Simple2DMesh.vert.spv");
    pipelineBuilder._shaderStages.push_back(
        vkinit::pipeline_shader_stage_create_info(VK_SHADER_STAGE_VERTEX_BIT, *simpleMeshVertShader));

    //make sure that triangleFragShader is holding the compiled colored_triangle.frag
    const auto simpleMeshFragShader = ShaderModule::CreateFragmentShaderModule(_device, "Simple2DMesh.frag.spv");
    pipelineBuilder._shaderStages.push_back(
        vkinit::pipeline_shader_stage_create_info(VK_SHADER_STAGE_FRAGMENT_BIT, *simpleMeshFragShader));

    pipelineBuilder._pipelineLayout = simpleMeshPipelineLayout;

    //build the mesh triangle pipeline
    simpleMeshPipeline = pipelineBuilder.BuildPipeline(_device, _renderPass);

    _mainDeletionQueue.PushDeletor
    (
        [=]()
        {
            //destroy the pipelines we have created
            vkDestroyPipeline(_device, _rainbowTrianglePipeline, nullptr);
            vkDestroyPipeline(_device, _meshPipeline, nullptr);
            vkDestroyPipeline(_device, simpleMeshPipeline, nullptr);

            //destroy the pipeline layout that they use
            vkDestroyPipelineLayout(_device, _trianglePipelineLayout, nullptr);
            vkDestroyPipelineLayout(_device, _meshPipelineLayout, nullptr);
            vkDestroyPipelineLayout(_device, simpleMeshPipelineLayout, nullptr);
        }
    );
}

static void check_vk_result(VkResult err)
{
    if (err == 0)
        return;
    fprintf(stderr, "[vulkan] Error: VkResult = %d\n", err);
    if (err < 0)
        abort();
}

void RenderingECSModule::InitImGUI()
{
    //1: create descriptor pool for IMGUI
    // the size of the pool is very oversize, but it's copied from imgui demo itself.
    VkDescriptorPoolSize pool_sizes[] =
    {
        { VK_DESCRIPTOR_TYPE_SAMPLER, 1000 },
        { VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER, 1000 },
        { VK_DESCRIPTOR_TYPE_SAMPLED_IMAGE, 1000 },
        { VK_DESCRIPTOR_TYPE_STORAGE_IMAGE, 1000 },
        { VK_DESCRIPTOR_TYPE_UNIFORM_TEXEL_BUFFER, 1000 },
        { VK_DESCRIPTOR_TYPE_STORAGE_TEXEL_BUFFER, 1000 },
        { VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER, 1000 },
        { VK_DESCRIPTOR_TYPE_STORAGE_BUFFER, 1000 },
        { VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER_DYNAMIC, 1000 },
        { VK_DESCRIPTOR_TYPE_STORAGE_BUFFER_DYNAMIC, 1000 },
        { VK_DESCRIPTOR_TYPE_INPUT_ATTACHMENT, 1000 }
    };

    VkDescriptorPoolCreateInfo pool_info = {};
    pool_info.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO;
    pool_info.flags = VK_DESCRIPTOR_POOL_CREATE_FREE_DESCRIPTOR_SET_BIT;
    pool_info.maxSets = 1000;
    pool_info.poolSizeCount = (uint32_t)std::size(pool_sizes);
    pool_info.pPoolSizes = pool_sizes;

    VkDescriptorPool imguiPool;
    VK_CHECK(vkCreateDescriptorPool(_device, &pool_info, nullptr, &imguiPool));

    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    // io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;         // IF using Docking Branch

    // Setup Platform/Renderer backends
    ImGui_ImplSDL2_InitForVulkan(_window);
    ImGui_ImplVulkan_InitInfo init_info = {};
    init_info.Instance = _instance;
    init_info.PhysicalDevice = _chosenGPU;
    init_info.Device = _device;
    init_info.QueueFamily = _graphicsQueueFamily;
    init_info.Queue = _graphicsQueue;
    // init_info.PipelineCache = YOUR_PIPELINE_CACHE;
    init_info.DescriptorPool = imguiPool;
    init_info.Subpass = 0;
    init_info.MinImageCount = 2;
    init_info.ImageCount = 2;
    init_info.MSAASamples = VK_SAMPLE_COUNT_1_BIT;
    // init_info.Allocator = YOUR_ALLOCATOR;
    init_info.CheckVkResultFn = check_vk_result;
    ImGui_ImplVulkan_Init(&init_info, _renderPass);

    // add the destroy the imgui created structures
     _mainDeletionQueue.PushDeletor
     (
         [=]()
         {
             vkDestroyDescriptorPool(_device, imguiPool, nullptr);
         }
     );
}

void RenderingECSModule::PreDrawStep(float deltaTime)
{
    // Start the Dear ImGui frame
    ImGui_ImplVulkan_NewFrame();
    ImGui_ImplSDL2_NewFrame();
    ImGui::NewFrame();

    //wait until the GPU has finished rendering the last frame. Timeout of 1 second
    VK_CHECK(vkWaitForFences(_device, 1, &_renderFence, true, 1000000000));
    VK_CHECK(vkResetFences(_device, 1, &_renderFence));

    //request image from the swapchain, one second timeout
    VK_CHECK(vkAcquireNextImageKHR(_device, _swapchain, 1000000000, _presentSemaphore, nullptr, &swapchainImageIndex));

    //now that we are sure that the commands finished executing, we can safely reset the command buffer to begin recording again.
    VK_CHECK(vkResetCommandBuffer(_mainCommandBuffer, 0));

    //begin the command buffer recording. We will use this command buffer exactly once, so we want to let Vulkan know that
    VkCommandBufferBeginInfo cmdBeginInfo = {};
    cmdBeginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
    cmdBeginInfo.pNext = nullptr;

    cmdBeginInfo.pInheritanceInfo = nullptr;
    cmdBeginInfo.flags = VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT;

    VK_CHECK(vkBeginCommandBuffer(_mainCommandBuffer, &cmdBeginInfo));

    //make a clear-color from frame number. This will flash with a 120*pi frame period.
    VkClearValue clearValue = {};
    float flash = abs(sin(_frameNumber / 3840.f));
    clearValue.color = { { 0.0f, 0.0f, flash, 1.0f } };

    //start the main renderpass.
    //We will use the clear color from above, and the framebuffer of the index the swapchain gave us
    VkRenderPassBeginInfo rpInfo = {};
    rpInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
    rpInfo.pNext = nullptr;

    rpInfo.renderPass = _renderPass;
    rpInfo.renderArea.offset.x = 0;
    rpInfo.renderArea.offset.y = 0;
    rpInfo.renderArea.extent = windowExtent;
    rpInfo.framebuffer = _framebuffers[swapchainImageIndex];

    //connect clear values
    rpInfo.clearValueCount = 1;
    rpInfo.pClearValues = &clearValue;

    vkCmdBeginRenderPass(_mainCommandBuffer, &rpInfo, VK_SUBPASS_CONTENTS_INLINE);
}

void RenderingECSModule::PostDrawStep(float deltaTime)
{
    // Rendering imgui
    ImGui::Render();
    ImGui_ImplVulkan_RenderDrawData(ImGui::GetDrawData(), _mainCommandBuffer);

    //finalize the render pass
    vkCmdEndRenderPass(_mainCommandBuffer);
    //finalize the command buffer (we can no longer add commands, but it can now be executed)
    VK_CHECK(vkEndCommandBuffer(_mainCommandBuffer));


    //prepare the submission to the queue.
    //we want to wait on the _presentSemaphore, as that semaphore is signaled when the swapchain is ready
    //we will signal the _renderSemaphore, to signal that rendering has finished

    VkSubmitInfo submit = {};
    submit.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
    submit.pNext = nullptr;

    VkPipelineStageFlags waitStage = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;

    submit.pWaitDstStageMask = &waitStage;

    submit.waitSemaphoreCount = 1;
    submit.pWaitSemaphores = &_presentSemaphore;

    submit.signalSemaphoreCount = 1;
    submit.pSignalSemaphores = &_renderSemaphore;

    submit.commandBufferCount = 1;
    submit.pCommandBuffers = &_mainCommandBuffer;

    //submit command buffer to the queue and execute it.
    // _renderFence will now block until the graphic commands finish execution
    VK_CHECK(vkQueueSubmit(_graphicsQueue, 1, &submit, _renderFence));


    // this will put the image we just rendered into the visible window.
    // we want to wait on the _renderSemaphore for that,
    // as it's necessary that drawing commands have finished before the image is displayed to the user
    VkPresentInfoKHR presentInfo = {};
    presentInfo.sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR;
    presentInfo.pNext = nullptr;

    presentInfo.pSwapchains = &_swapchain;
    presentInfo.swapchainCount = 1;

    presentInfo.pWaitSemaphores = &_renderSemaphore;
    presentInfo.waitSemaphoreCount = 1;

    presentInfo.pImageIndices = &swapchainImageIndex;

    VkResult result = vkQueuePresentKHR(_graphicsQueue, &presentInfo);
    if (result == VK_ERROR_OUT_OF_DATE_KHR || result == VK_SUBOPTIMAL_KHR)
    {
    }
    else
    {
        VK_CHECK(result);
    }

    //increase the number of frames drawn
    _frameNumber++;
}

void RenderingECSModule::Draw
(
    const float deltaTime,
    const glm::mat4 renderMatrix,
    const SimpleMesh& mesh,
    const Material& material
)
{
    vkCmdBindPipeline(_mainCommandBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, material.pipeline);

    VkViewport viewport = {};
    viewport.x = 0.0f;
    viewport.y = 0.0f;
    viewport.width = static_cast<float>(windowExtent.width);
    viewport.height = static_cast<float>(windowExtent.height);
    viewport.minDepth = 0.0f;
    viewport.maxDepth = 1.0f;

    VkRect2D scissor = {};
    scissor.offset = {0, 0};
    scissor.extent = {static_cast<uint32_t>(windowExtent.width), static_cast<uint32_t>(windowExtent.height)};

    vkCmdSetViewport(_mainCommandBuffer, 0, 1, &viewport);
    vkCmdSetScissor(_mainCommandBuffer, 0, 1, &scissor);

    //bind the mesh vertex buffer with offset 0
    VkDeviceSize offset = 0;
    vkCmdBindVertexBuffers(_mainCommandBuffer, 0, 1, &mesh._vertexBuffer._buffer, &offset);

    vkCmdBindIndexBuffer(_mainCommandBuffer, mesh._indexBuffer._buffer, 0, VK_INDEX_TYPE_UINT32);

    MeshPushConstants constants = {};
    
    constants.color = material.color;
    constants.renderMatrix = renderMatrix;

    //upload the matrix to the GPU via push constants
    vkCmdPushConstants(_mainCommandBuffer, material.pipelineLayout, VK_SHADER_STAGE_VERTEX_BIT | VK_SHADER_STAGE_FRAGMENT_BIT, 0, sizeof(MeshPushConstants), &constants);

    //we can now draw the mesh
    vkCmdDrawIndexed(_mainCommandBuffer, (uint32_t)mesh._indices.size(), 1, 0, 0, 0);
}

template<typename TMesh>
void RenderingECSModule::UploadMesh(TMesh& mesh)
{
    //allocate vertex buffer
    VkBufferCreateInfo bufferInfo = {};
    bufferInfo.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
    //this is the total size, in bytes, of the buffer we are allocating
    bufferInfo.size = mesh._vertices.size() * sizeof(SimpleVertex);
    //this buffer is going to be used as a Vertex Buffer
    bufferInfo.usage = VK_BUFFER_USAGE_VERTEX_BUFFER_BIT;


    //let the VMA library know that this data should be writeable by CPU, but also readable by GPU
    VmaAllocationCreateInfo vmaallocInfo = {};
    vmaallocInfo.usage = VMA_MEMORY_USAGE_CPU_TO_GPU;

    // Allocate vertex buffer
    VK_CHECK(vmaCreateBuffer(_allocator, &bufferInfo, &vmaallocInfo,
        &mesh._vertexBuffer._buffer,
        &mesh._vertexBuffer._allocation,
        nullptr));
    
    // Allocate index buffer
    VkBufferCreateInfo indexBufferInfo = {};
    indexBufferInfo.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
    indexBufferInfo.size = mesh._indices.size() * sizeof(uint32_t); // Size of index buffer in bytes
    indexBufferInfo.usage = VK_BUFFER_USAGE_INDEX_BUFFER_BIT;

    VmaAllocationCreateInfo indexAllocInfo = {};
    indexAllocInfo.usage = VMA_MEMORY_USAGE_CPU_TO_GPU;

    // Allocate the index buffer
    VK_CHECK(vmaCreateBuffer(_allocator, &indexBufferInfo, &indexAllocInfo,
        &mesh._indexBuffer._buffer,
        &mesh._indexBuffer._allocation,
        nullptr));

    //add the destruction of triangle mesh buffer to the deletion queue
    _mainDeletionQueue.PushDeletor
    (
        [=]()
        {
            vmaDestroyBuffer(_allocator, mesh._vertexBuffer._buffer, mesh._vertexBuffer._allocation);
            vmaDestroyBuffer(_allocator, mesh._indexBuffer._buffer, mesh._indexBuffer._allocation);
        }
    );

    //copy vertex data
    void* vertexData;
    vmaMapMemory(_allocator, mesh._vertexBuffer._allocation, &vertexData);
    memcpy(vertexData, mesh._vertices.data(), mesh._vertices.size() * sizeof(SimpleVertex));
    vmaUnmapMemory(_allocator, mesh._vertexBuffer._allocation);

    // Copy index data
    void* indexData;
    vmaMapMemory(_allocator, mesh._indexBuffer._allocation, &indexData);
    memcpy(indexData, mesh._indices.data(), mesh._indices.size() * sizeof(uint32_t));
    vmaUnmapMemory(_allocator, mesh._indexBuffer._allocation);
}

} // namespace velecs
