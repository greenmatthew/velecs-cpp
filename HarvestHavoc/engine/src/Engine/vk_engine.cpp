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
#include "Engine/vk_initializers.h"
#include "Engine/vk_pipeline.h"
#include "Engine/vk_shaders.h"

#include "Graphics/Color32.h"

#include "FileManagement/Path.h"

#include <iostream>
#include <fstream>
#include <chrono>

#include <SDL2/SDL.h>
#include <SDL2/SDL_vulkan.h>

#include <VkBootstrap/VkBootstrap.h>

#include <imgui/imgui.h>
#include <imgui/imgui_impl_sdl.h>
#include <imgui/imgui_impl_vulkan.h>

namespace engine {

// Public Fields

// Constructors and Destructors

// Public Methods

VulkanEngine& VulkanEngine::Init()
{
    ecsManager->Init();

    // We initialize SDL and create a window with it. 
    SDL_Init(SDL_INIT_VIDEO);

    SDL_WindowFlags window_flags = (SDL_WindowFlags)(SDL_WINDOW_VULKAN);

    ecsManager->ecs.get<GlobalData>()->camera;

    _window = SDL_CreateWindow(
        "Harvest Havoc",
        SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,
        _windowExtent.width,
        _windowExtent.height,
        window_flags
    );

    //everything went fine
    _isInitialized = true;
    return *this;
}

// VulkanEngine& VulkanEngine::SetInput(std::unique_ptr<IInput> input)
// {
//     this->input = std::move(input);
//     return *this;
// }

VulkanEngine& VulkanEngine::SetECS(std::unique_ptr<IECSManager> ecsManager)
{
    this->ecsManager = std::move(ecsManager);
    return *this;
}

VulkanEngine& VulkanEngine::Run()
{
    auto lastFrameTime = std::chrono::high_resolution_clock::now();

    while (!isQuitting)
    {
        auto currentFrameTime = std::chrono::high_resolution_clock::now();
        std::chrono::duration<float> elapsedTime = currentFrameTime - lastFrameTime;
        float deltaTime = elapsedTime.count();

        lastFrameTime = currentFrameTime;

        InputUpdate();

        ecsManager->ecs.progress(deltaTime);

        Draw(deltaTime);
    }
    return *this;
}

VulkanEngine& VulkanEngine::Cleanup()
{
    if (_isInitialized)
    {
        ecsManager->Cleanup();
    }
    return *this;
}

// Protected Fields

// Protected Methods

// Private Fields

// Private Methods

void VulkanEngine::InputUpdate()
{
    // input->HandleIEnableDisableRequests();

    // input->TrySettingToIdle();

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
                // input->TryOnPressed(keycode);
            }
            break;
        }
        case SDL_KEYUP:
        {
            SDL_Keycode keycode = event.key.keysym.sym;
            // input->TryOnReleased(keycode);
            break;
        }
        default:
            break;
        }
    }

    // input->TryOnHeld();
}

void VulkanEngine::Draw(const float deltaTime)
{
//     //wait until the GPU has finished rendering the last frame. Timeout of 1 second
//     VK_CHECK(vkWaitForFences(_device, 1, &_renderFence, true, 1000000000));
//     VK_CHECK(vkResetFences(_device, 1, &_renderFence));

//     //request image from the swapchain, one second timeout
//     uint32_t swapchainImageIndex;
//     VK_CHECK(vkAcquireNextImageKHR(_device, _swapchain, 1000000000, _presentSemaphore, nullptr, &swapchainImageIndex));

//     //now that we are sure that the commands finished executing, we can safely reset the command buffer to begin recording again.
//     VK_CHECK(vkResetCommandBuffer(_mainCommandBuffer, 0));

//         //naming it cmd for shorter writing
//     VkCommandBuffer cmd = _mainCommandBuffer;

//     //begin the command buffer recording. We will use this command buffer exactly once, so we want to let Vulkan know that
//     VkCommandBufferBeginInfo cmdBeginInfo = {};
//     cmdBeginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
//     cmdBeginInfo.pNext = nullptr;

//     cmdBeginInfo.pInheritanceInfo = nullptr;
//     cmdBeginInfo.flags = VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT;

//     VK_CHECK(vkBeginCommandBuffer(cmd, &cmdBeginInfo));

//     //make a clear-color from frame number. This will flash with a 120*pi frame period.
//     VkClearValue clearValue = {};
//     float flash = abs(sin(_frameNumber / 3840.f));
//     clearValue.color = { { 0.0f, 0.0f, flash, 1.0f } };

//     //start the main renderpass.
//     //We will use the clear color from above, and the framebuffer of the index the swapchain gave us
//     VkRenderPassBeginInfo rpInfo = {};
//     rpInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
//     rpInfo.pNext = nullptr;

//     rpInfo.renderPass = _renderPass;
//     rpInfo.renderArea.offset.x = 0;
//     rpInfo.renderArea.offset.y = 0;
//     rpInfo.renderArea.extent = _windowExtent;
//     rpInfo.framebuffer = _framebuffers[swapchainImageIndex];

//     //connect clear values
//     rpInfo.clearValueCount = 1;
//     rpInfo.pClearValues = &clearValue;

//     vkCmdBeginRenderPass(cmd, &rpInfo, VK_SUBPASS_CONTENTS_INLINE);

//     //once we start adding rendering commands, they will go here
//     switch (renderPipelineIndex)
//     {
//         case 0:
//             vkCmdBindPipeline(cmd, VK_PIPELINE_BIND_POINT_GRAPHICS, _trianglePipeline);
//             vkCmdDraw(cmd, 3, 1, 0, 0);
//             break;
//         case 1:
//             vkCmdBindPipeline(cmd, VK_PIPELINE_BIND_POINT_GRAPHICS, _redTrianglePipeline);
//             vkCmdDraw(cmd, 3, 1, 0, 0);
//             break;
//         case 2:
//             vkCmdBindPipeline(cmd, VK_PIPELINE_BIND_POINT_GRAPHICS, _triangleWireFramePipeline);
//             vkCmdDraw(cmd, 3, 1, 0, 0);
//             break;
//         case 3:
//             vkCmdBindPipeline(cmd, VK_PIPELINE_BIND_POINT_GRAPHICS, _rainbowTrianglePipeline);
//             vkCmdDraw(cmd, 3, 1, 0, 0);
//             break;
//         case 4:
//         {
//             vkCmdBindPipeline(cmd, VK_PIPELINE_BIND_POINT_GRAPHICS, _meshPipeline);

//             //bind the mesh vertex buffer with offset 0
//             VkDeviceSize offset = 0;
//             vkCmdBindVertexBuffers(cmd, 0, 1, &_triangleMesh._vertexBuffer._buffer, &offset);

//             //make a model view matrix for rendering the object
//             //camera position
//             glm::vec3 camPos = { 0.f,0.f,-2.f };

//             glm::mat4 view = glm::translate(glm::mat4(1.f), camPos);
//             //camera projection
//             glm::mat4 projection = glm::perspective(glm::radians(70.f), _windowExtent.width / (float)_windowExtent.height, 0.1f, 200.0f);
//             projection[1][1] *= -1;
//             //model rotation
//             static float cumulativeAngle = 0.0f;
//             cumulativeAngle += deltaTime * 100.0f;
//             glm::mat4 model = glm::rotate(glm::mat4{ 1.0f }, glm::radians(cumulativeAngle), glm::vec3(0, 1, 0));

//             //calculate final mesh matrix
//             glm::mat4 meshMatrix = projection * view * model;

//             MeshPushConstants constants = {};
//             constants.renderMatrix = meshMatrix;

//             //upload the matrix to the GPU via push constants
//             vkCmdPushConstants(cmd, _meshPipelineLayout, VK_SHADER_STAGE_VERTEX_BIT, 0, sizeof(MeshPushConstants), &constants);

//             //we can now draw the mesh
//             vkCmdDraw(cmd, (uint32_t)_triangleMesh._vertices.size(), 1, 0, 0);
//             break;
//         }
//         default:
//             std::cout << "Unknown render pipeline" << std::endl;
//             break;
//     }

//     //finalize the render pass
//     vkCmdEndRenderPass(cmd);
//     //finalize the command buffer (we can no longer add commands, but it can now be executed)
//     VK_CHECK(vkEndCommandBuffer(cmd));


//     //prepare the submission to the queue.
//     //we want to wait on the _presentSemaphore, as that semaphore is signaled when the swapchain is ready
//     //we will signal the _renderSemaphore, to signal that rendering has finished

//     VkSubmitInfo submit = {};
//     submit.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
//     submit.pNext = nullptr;

//     VkPipelineStageFlags waitStage = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;

//     submit.pWaitDstStageMask = &waitStage;

//     submit.waitSemaphoreCount = 1;
//     submit.pWaitSemaphores = &_presentSemaphore;

//     submit.signalSemaphoreCount = 1;
//     submit.pSignalSemaphores = &_renderSemaphore;

//     submit.commandBufferCount = 1;
//     submit.pCommandBuffers = &cmd;

//     //submit command buffer to the queue and execute it.
//     // _renderFence will now block until the graphic commands finish execution
//     VK_CHECK(vkQueueSubmit(_graphicsQueue, 1, &submit, _renderFence));


//     // this will put the image we just rendered into the visible window.
//     // we want to wait on the _renderSemaphore for that,
//     // as it's necessary that drawing commands have finished before the image is displayed to the user
//     VkPresentInfoKHR presentInfo = {};
//     presentInfo.sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR;
//     presentInfo.pNext = nullptr;

//     presentInfo.pSwapchains = &_swapchain;
//     presentInfo.swapchainCount = 1;

//     presentInfo.pWaitSemaphores = &_renderSemaphore;
//     presentInfo.waitSemaphoreCount = 1;

//     presentInfo.pImageIndices = &swapchainImageIndex;

//     VK_CHECK(vkQueuePresentKHR(_graphicsQueue, &presentInfo));

//     //increase the number of frames drawn
//     _frameNumber++;
}

} // namespace engine
