/// \file    vk_engine.cpp
/// \author  Matthew Green
/// \date    10/15/2023 14:57:55
/// 
/// \section LICENSE
/// 
/// Copyright (c) 2023 Matthew Green - All rights reserved
/// Unauthorized copying of this file, via any medium is strictly prohibited
/// Proprietary and confidential

#include "Engine/vk_engine.h"
#include "Engine/vk_types.h"
#include "Engine/vk_initializers.h"
#include "Engine/vk_pipeline.h"
#include "Engine/vk_shaders.h"

#include "Core/Path.h"

#include "Input/Input.h"
#include "Input/InputActionMap.h"
#include "Input/InputAction.h"

#include <iostream>
#include <fstream>

#include <SDL2/SDL.h>
#include <SDL2/SDL_vulkan.h>

#include <VkBootstrap/VkBootstrap.h>

#include <imgui/imgui.h>
#include <imgui/imgui_impl_sdl.h>
#include <imgui/imgui_impl_vulkan.h>

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

using namespace HarvestHavoc::Input;

namespace HarvestHavoc::Engine {

// Public Fields

// Constructors and Destructors

// Public Methods

void VulkanEngine::Init()
{
    std::cout << HarvestHavoc::Path::GAME_DIR << std::endl;

    // We initialize SDL and create a window with it. 
    SDL_Init(SDL_INIT_VIDEO);

    SDL_WindowFlags window_flags = (SDL_WindowFlags)(SDL_WINDOW_VULKAN);
    
    _window = SDL_CreateWindow(
        "Harvest Havoc",
        SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,
        _windowExtent.width,
        _windowExtent.height,
        window_flags
    );

    InitVulkan();
    InitSwapchain();
    InitCommands();
    InitDefaultRenderPass();
    InitFrameBuffers();
    InitSyncStructures();
    InitPipelines();

    InitImGUI();

    InitInput();

    //everything went fine
    _isInitialized = true;
}

void VulkanEngine::Cleanup()
{
    if (_isInitialized)
    {
        VK_CHECK(vkWaitForFences(_device, 1, &_renderFence, true, 1000000000));

        // cleanup in reverse order to initialization.

        vkDestroySemaphore(_device, _renderSemaphore, nullptr);
        vkDestroySemaphore(_device, _presentSemaphore, nullptr);
        vkDestroyFence(_device, _renderFence, nullptr);

        vkDestroyCommandPool(_device, _commandPool, nullptr);

        vkDestroySwapchainKHR(_device, _swapchain, nullptr);

        //destroy the main renderpass
        vkDestroyRenderPass(_device, _renderPass, nullptr);

        //destroy swapchain resources
        for (int i = 0; i < _framebuffers.size(); i++)
        {
            vkDestroyFramebuffer(_device, _framebuffers[i], nullptr);

            vkDestroyImageView(_device, _swapchainImageViews[i], nullptr);
        }

        vkDestroyDevice(_device, nullptr);
        vkDestroySurfaceKHR(_instance, _surface, nullptr);
        vkb::destroy_debug_utils_messenger(_instance, _debug_messenger);
        vkDestroyInstance(_instance, nullptr);
        SDL_DestroyWindow(_window);
    }
}

void VulkanEngine::Run()
{
    while (!isQuitting)
    {
        InputUpdate();

        Draw();
    }
}

// Protected Fields

// Protected Methods

// Private Fields

// Private Methods

void VulkanEngine::InitVulkan()
{
    vkb::InstanceBuilder builder;

    auto inst_ret = builder.set_app_name("HarvestHavoc")
    #ifdef _DEBUG
        .request_validation_layers(true)
    #endif
        .require_api_version(1, 1, 0)
        .use_default_debug_messenger()
        .build();
    
    vkb::Instance vkb_inst = inst_ret.value();

    //store the instance
    _instance = vkb_inst.instance;
    //store the debug messenger
    _debug_messenger = vkb_inst.debug_messenger;

    // get the surface of the window we opened with SDL
    SDL_Vulkan_CreateSurface(_window, _instance, &_surface);

    //use vkbootstrap to select a GPU.
    //We want a GPU that can write to the SDL surface and supports Vulkan 1.1
    vkb::PhysicalDeviceSelector selector{ vkb_inst };
    vkb::PhysicalDevice physicalDevice = selector
        .set_minimum_version(1, 1)
        .set_surface(_surface)
        .select()
        .value();

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
}

void VulkanEngine::InitSwapchain()
{
    vkb::SwapchainBuilder swapchainBuilder{ _chosenGPU,_device,_surface };

    vkb::Swapchain vkbSwapchain = swapchainBuilder
        .use_default_format_selection()
        //use vsync present mode
        // .set_desired_present_mode(VK_PRESENT_MODE_FIFO_KHR)
        // .set_desired_extent(_windowExtent.width, _windowExtent.height)
        .build()
        .value();
    
    vkbSwapchain.extent = _windowExtent;
    vkbSwapchain.present_mode = VK_PRESENT_MODE_FIFO_KHR;

    //store swapchain and its related images
    _swapchain = vkbSwapchain.swapchain;
    _swapchainImages = vkbSwapchain.get_images().value();
    _swapchainImageViews = vkbSwapchain.get_image_views().value();

    _swapchainImageFormat = vkbSwapchain.image_format;
}

void VulkanEngine::InitCommands()
{
    //create a command pool for commands submitted to the graphics queue.
    //we also want the pool to allow for resetting of individual command buffers
    VkCommandPoolCreateInfo commandPoolInfo = vkinit::command_pool_create_info(_graphicsQueueFamily, VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT);

    VK_CHECK(vkCreateCommandPool(_device, &commandPoolInfo, nullptr, &_commandPool));

    //allocate the default command buffer that we will use for rendering
    VkCommandBufferAllocateInfo cmdAllocInfo = vkinit::command_buffer_allocate_info(_commandPool, 1);

    VK_CHECK(vkAllocateCommandBuffers(_device, &cmdAllocInfo, &_mainCommandBuffer));
}

void VulkanEngine::InitDefaultRenderPass()
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

void VulkanEngine::InitFrameBuffers()
{
    //create the framebuffers for the swapchain images. This will connect the render-pass to the images for rendering
    VkFramebufferCreateInfo fb_info = {};
    fb_info.sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;
    fb_info.pNext = nullptr;

    fb_info.renderPass = _renderPass;
    fb_info.attachmentCount = 1;
    fb_info.width = _windowExtent.width;
    fb_info.height = _windowExtent.height;
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

void VulkanEngine::InitSyncStructures()
{
    VkFenceCreateInfo fenceCreateInfo = {};
    fenceCreateInfo.sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO;
    fenceCreateInfo.pNext = nullptr;

    //we want to create the fence with the Create Signaled flag, so we can wait on it before using it on a GPU command (for the first frame)
    fenceCreateInfo.flags = VK_FENCE_CREATE_SIGNALED_BIT;

    VK_CHECK(vkCreateFence(_device, &fenceCreateInfo, nullptr, &_renderFence));

    //for the semaphores we don't need any flags
    VkSemaphoreCreateInfo semaphoreCreateInfo = {};
    semaphoreCreateInfo.sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO;
    semaphoreCreateInfo.pNext = nullptr;
    semaphoreCreateInfo.flags = 0;

    VK_CHECK(vkCreateSemaphore(_device, &semaphoreCreateInfo, nullptr, &_presentSemaphore));
    VK_CHECK(vkCreateSemaphore(_device, &semaphoreCreateInfo, nullptr, &_renderSemaphore));
}

void VulkanEngine::InitPipelines()
{
    VkShaderModule triangleFragShader;
    if (!ShaderModule::LoadFragmentShader(_device, "ColoredTriangle.frag.spv", &triangleFragShader))
    {
        std::cout << "Error when building the triangle fragment shader module" << std::endl;
    }
    else
    {
        std::cout << "Triangle fragment shader successfully loaded" << std::endl;
    }

    VkShaderModule triangleVertexShader;
    if (!ShaderModule::LoadVertexShader(_device, "ColoredTriangle.vert.spv", &triangleVertexShader))
    {
        std::cout << "Error when building the triangle vertex shader module" << std::endl;
    }
    else
    {
        std::cout << "Triangle vertex shader successfully loaded" << std::endl;
    }

    //build the pipeline layout that controls the inputs/outputs of the shader
    //we are not using descriptor sets or other systems yet, so no need to use anything other than empty default
    VkPipelineLayoutCreateInfo pipeline_layout_info = vkinit::pipeline_layout_create_info();

    VK_CHECK(vkCreatePipelineLayout(_device, &pipeline_layout_info, nullptr, &_trianglePipelineLayout));


    //build the stage-create-info for both vertex and fragment stages. This lets the pipeline know the shader modules per stage
    PipelineBuilder pipelineBuilder;

    pipelineBuilder._shaderStages.push_back(vkinit::pipeline_shader_stage_create_info(VK_SHADER_STAGE_VERTEX_BIT, triangleVertexShader));

    pipelineBuilder._shaderStages.push_back(vkinit::pipeline_shader_stage_create_info(VK_SHADER_STAGE_FRAGMENT_BIT, triangleFragShader));


    //vertex input controls how to read vertices from vertex buffers. We aren't using it yet
    pipelineBuilder._vertexInputInfo = vkinit::vertex_input_state_create_info();

    //input assembly is the configuration for drawing triangle lists, strips, or individual points.
    //we are just going to draw triangle list
    pipelineBuilder._inputAssembly = vkinit::input_assembly_create_info(VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST);

    //build viewport and scissor from the swapchain extents
    pipelineBuilder._viewport.x = 0.0f;
    pipelineBuilder._viewport.y = 0.0f;
    pipelineBuilder._viewport.width = (float)_windowExtent.width;
    pipelineBuilder._viewport.height = (float)_windowExtent.height;
    pipelineBuilder._viewport.minDepth = 0.0f;
    pipelineBuilder._viewport.maxDepth = 1.0f;

    pipelineBuilder._scissor.offset = { 0, 0 };
    pipelineBuilder._scissor.extent = _windowExtent;

    //configure the rasterizer to draw filled triangles
    pipelineBuilder._rasterizer = vkinit::rasterization_state_create_info(VK_POLYGON_MODE_FILL);

    //we don't use multisampling, so just run the default one
    pipelineBuilder._multisampling = vkinit::multisampling_state_create_info();

    //a single blend attachment with no blending and writing to RGBA
    pipelineBuilder._colorBlendAttachment = vkinit::color_blend_attachment_state();

    //use the triangle layout we created
    pipelineBuilder._pipelineLayout = _trianglePipelineLayout;

    //finally build the pipeline
    _trianglePipeline = pipelineBuilder.BuildPipeline(_device, _renderPass);
}

void VulkanEngine::InitImGUI()
{
    // //1: create descriptor pool for IMGUI
    // // the size of the pool is very oversize, but it's copied from imgui demo itself.
    // VkDescriptorPoolSize pool_sizes[] =
    // {
    //     { VK_DESCRIPTOR_TYPE_SAMPLER, 1000 },
    //     { VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER, 1000 },
    //     { VK_DESCRIPTOR_TYPE_SAMPLED_IMAGE, 1000 },
    //     { VK_DESCRIPTOR_TYPE_STORAGE_IMAGE, 1000 },
    //     { VK_DESCRIPTOR_TYPE_UNIFORM_TEXEL_BUFFER, 1000 },
    //     { VK_DESCRIPTOR_TYPE_STORAGE_TEXEL_BUFFER, 1000 },
    //     { VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER, 1000 },
    //     { VK_DESCRIPTOR_TYPE_STORAGE_BUFFER, 1000 },
    //     { VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER_DYNAMIC, 1000 },
    //     { VK_DESCRIPTOR_TYPE_STORAGE_BUFFER_DYNAMIC, 1000 },
    //     { VK_DESCRIPTOR_TYPE_INPUT_ATTACHMENT, 1000 }
    // };

    // VkDescriptorPoolCreateInfo pool_info = {};
    // pool_info.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO;
    // pool_info.flags = VK_DESCRIPTOR_POOL_CREATE_FREE_DESCRIPTOR_SET_BIT;
    // pool_info.maxSets = 1000;
    // pool_info.poolSizeCount = std::size(pool_sizes);
    // pool_info.pPoolSizes = pool_sizes;

    // VkDescriptorPool imguiPool;
    // VK_CHECK(vkCreateDescriptorPool(_device, &pool_info, nullptr, &imguiPool));


    // // 2: initialize imgui library

    // //this initializes the core structures of imgui
    // ImGui::CreateContext();

    // //this initializes imgui for SDL
    // ImGui_ImplSDL2_InitForVulkan(_window);

    // //this initializes imgui for Vulkan
    // ImGui_ImplVulkan_InitInfo init_info = {};
    // init_info.Instance = _instance;
    // init_info.PhysicalDevice = _chosenGPU;
    // init_info.Device = _device;
    // init_info.Queue = _graphicsQueue;
    // init_info.DescriptorPool = imguiPool;
    // init_info.MinImageCount = 3;
    // init_info.ImageCount = 3;
    // init_info.MSAASamples = VK_SAMPLE_COUNT_1_BIT;

    // ImGui_ImplVulkan_Init(&init_info, _renderPass);

    // //execute a gpu command to upload imgui font textures
    // immediate_submit([&](VkCommandBuffer cmd) {
    //     ImGui_ImplVulkan_CreateFontsTexture(cmd);
    //     });

    // //clear font textures from cpu data
    // ImGui_ImplVulkan_DestroyFontUploadObjects();

    // //add the destroy the imgui created structures
    // _mainDeletionQueue.push_function([=]() {

    //     vkDestroyDescriptorPool(_device, imguiPool, nullptr);
    //     ImGui_ImplVulkan_Shutdown();
    //     });
}

void VulkanEngine::InitInput()
{
    Input::Input::GetInstance().Init();
    Input::Input::GetInstance().Player->Switch();
}

void VulkanEngine::InputUpdate()
{
    Input::Input::GetInstance().HandleIEnableDisableRequests();

    Input::Input::GetInstance().TrySettingToIdle();

    //Handle events on queue
    while (SDL_PollEvent(&event) != 0)
    {
        switch (event.type)
        {
        case SDL_QUIT:
            isQuitting = true; //close the window when user alt-f4s or clicks the X button
            break;
        case SDL_KEYDOWN:
        {
            SDL_Keycode keycode = event.key.keysym.sym;
            if (event.key.repeat == 0)
            {
                Input::Input::GetInstance().TryOnPressed(keycode);
            }
            break;
        }
        case SDL_KEYUP:
        {
            SDL_Keycode keycode = event.key.keysym.sym;
            Input::Input::GetInstance().TryOnReleased(keycode);
            break;
        }
        default:
            break;
        }
    }

    Input::Input::GetInstance().TryOnHeld();
}

void VulkanEngine::Draw()
{
    //wait until the GPU has finished rendering the last frame. Timeout of 1 second
    VK_CHECK(vkWaitForFences(_device, 1, &_renderFence, true, 1000000000));
    VK_CHECK(vkResetFences(_device, 1, &_renderFence));

    //request image from the swapchain, one second timeout
    uint32_t swapchainImageIndex;
    VK_CHECK(vkAcquireNextImageKHR(_device, _swapchain, 1000000000, _presentSemaphore, nullptr, &swapchainImageIndex));

    //now that we are sure that the commands finished executing, we can safely reset the command buffer to begin recording again.
    VK_CHECK(vkResetCommandBuffer(_mainCommandBuffer, 0));

        //naming it cmd for shorter writing
    VkCommandBuffer cmd = _mainCommandBuffer;

    //begin the command buffer recording. We will use this command buffer exactly once, so we want to let Vulkan know that
    VkCommandBufferBeginInfo cmdBeginInfo = {};
    cmdBeginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
    cmdBeginInfo.pNext = nullptr;

    cmdBeginInfo.pInheritanceInfo = nullptr;
    cmdBeginInfo.flags = VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT;

    VK_CHECK(vkBeginCommandBuffer(cmd, &cmdBeginInfo));

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
    rpInfo.renderArea.extent = _windowExtent;
    rpInfo.framebuffer = _framebuffers[swapchainImageIndex];

    //connect clear values
    rpInfo.clearValueCount = 1;
    rpInfo.pClearValues = &clearValue;

    vkCmdBeginRenderPass(cmd, &rpInfo, VK_SUBPASS_CONTENTS_INLINE);

    //once we start adding rendering commands, they will go here

    vkCmdBindPipeline(cmd, VK_PIPELINE_BIND_POINT_GRAPHICS, _trianglePipeline);
    vkCmdDraw(cmd, 3, 1, 0, 0);

    //finalize the render pass
    vkCmdEndRenderPass(cmd);
    //finalize the command buffer (we can no longer add commands, but it can now be executed)
    VK_CHECK(vkEndCommandBuffer(cmd));


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
    submit.pCommandBuffers = &cmd;

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

    VK_CHECK(vkQueuePresentKHR(_graphicsQueue, &presentInfo));

    //increase the number of frames drawn
    _frameNumber++;
}

bool VulkanEngine::LoadShaderModule(const char* filePath, VkShaderModule* outShaderModule)
{
    //open the file. With cursor at the end
    std::ifstream file(filePath, std::ios::ate | std::ios::binary);
    if (!file.is_open())
    {
        return false;
    }

    //find what the size of the file is by looking up the location of the cursor
    //because the cursor is at the end, it gives the size directly in bytes
    size_t fileSize = (size_t)file.tellg();

    //spirv expects the buffer to be on uint32, so make sure to reserve an int vector big enough for the entire file
    std::vector<uint32_t> buffer(fileSize / sizeof(uint32_t));

    //put file cursor at beginning
    file.seekg(0);

    //load the entire file into the buffer
    file.read((char*)buffer.data(), fileSize);

    //now that the file is loaded into the buffer, we can close it
    file.close();

    //create a new shader module, using the buffer we loaded
    VkShaderModuleCreateInfo createInfo = {};
    createInfo.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
    createInfo.pNext = nullptr;

    //codeSize has to be in bytes, so multiply the ints in the buffer by size of int to know the real size of the buffer
    createInfo.codeSize = buffer.size() * sizeof(uint32_t);
    createInfo.pCode = buffer.data();

    //check that the creation goes well.
    VkShaderModule shaderModule;
    if (vkCreateShaderModule(_device, &createInfo, nullptr, &shaderModule) != VK_SUCCESS)
    {
        return false;
    }

    *outShaderModule = shaderModule;
    return true;
}

} // namespace HarvestHavoc::Engine
