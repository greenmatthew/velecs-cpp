/// \file    RenderingSystems.cpp
/// \author  Matthew Green
/// \date    10/31/2023 12:32:19
/// 
/// \section LICENSE
/// 
/// Copyright (c) 2023 Matthew Green - All rights reserved
/// Unauthorized copying of this file, via any medium is strictly prohibited
/// Proprietary and confidential

#include "ECS/RenderingECS.h"

#include <Engine/vk_engine.h>
#include <Engine/AllocatedBuffer.h>
#include <Engine/DeletionQueue.h>
#include <Engine/vk_initializers.h>
#include <Engine/vk_shaders.h>
#include <Engine/vk_pipeline.h>

#include <Graphics/MeshPushConstants.h>

namespace hh {

// Public Fields

// Constructors and Destructors

RenderingECS::RenderingECS(flecs::world& ecs, engine::VulkanEngine& engine)
    : IRenderingECS(ecs, engine) {}

// Public Methods

// Protected Fields

// Protected Methods

void RenderingECS::InitComponents()
{
    ecs.component<Transform>();
    ecs.component<Mesh>();
    ecs.component<Material>();
}

void RenderingECS::InitSystems()
{
    //ecs.system<Transform, Mesh, Material>()
    //    .kind<Draw>()
    //    .iter([](flecs::iter& it, Transform* transforms, Mesh* meshes, Material* materials)
    //    {
    //        float delta_time = it.delta_time();

    //        // Vulkan Start Code

    //        vkCmdBeginRenderPass(cmd, &rpInfo, VK_SUBPASS_CONTENTS_INLINE);

    //        for (auto i : it)
    //        {
    //            Transform transform = transforms[i];
    //            Mesh mesh = meshes[i];
    //            Material material = materials[i];

    //            vkCmdBindPipeline(cmd, VK_PIPELINE_BIND_POINT_GRAPHICS, material._meshPipeline);

    //            //bind the mesh vertex buffer with offset 0
    //            VkDeviceSize offset = 0;
    //            vkCmdBindVertexBuffers(cmd, 0, 1, &mesh._vertexBuffer._buffer, &offset);

    //            MeshPushConstants constants = {};
    //            constants.renderMatrix = mesh.GetRenderMatrix(material);

    //            //upload the matrix to the GPU via push constants
    //            vkCmdPushConstants(cmd, _meshPipelineLayout, VK_SHADER_STAGE_VERTEX_BIT, 0, sizeof(MeshPushConstants), &constants);

    //            //we can now draw the mesh
    //            vkCmdDraw(cmd, (uint32_t)_triangleMesh._vertices.size(), 1, 0, 0);
    //        }

    //        vkCmdEndRenderPass(cmd);

    //        // Vulkan End Code
    //    }
    //);

    //ecs.system<Transform, Mesh, Material>()
    //   .kind<Draw>()
    //   .iter([this](flecs::iter& it, Transform* transforms, Mesh* meshes, Material* materials)
    //   {
    //       float delta_time = it.delta_time();

    //       //wait until the GPU has finished rendering the last frame. Timeout of 1 second
    //        VK_CHECK(vkWaitForFences(engine._device, 1, &engine._renderFence, true, 1000000000));
    //        VK_CHECK(vkResetFences(engine._device, 1, &engine._renderFence));

    //        //request image from the swapchain, one second timeout
    //        uint32_t swapchainImageIndex;
    //        VK_CHECK(vkAcquireNextImageKHR(engine._device, engine._swapchain, 1000000000, engine._presentSemaphore, nullptr, &swapchainImageIndex));

    //        //now that we are sure that the commands finished executing, we can safely reset the command buffer to begin recording again.
    //        VK_CHECK(vkResetCommandBuffer(engine._mainCommandBuffer, 0));

    //            //naming it cmd for shorter writing
    //        VkCommandBuffer cmd = engine._mainCommandBuffer;

    //        //begin the command buffer recording. We will use this command buffer exactly once, so we want to let Vulkan know that
    //        VkCommandBufferBeginInfo cmdBeginInfo = {};
    //        cmdBeginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
    //        cmdBeginInfo.pNext = nullptr;

    //        cmdBeginInfo.pInheritanceInfo = nullptr;
    //        cmdBeginInfo.flags = VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT;

    //        VK_CHECK(vkBeginCommandBuffer(cmd, &cmdBeginInfo));

    //        //make a clear-color from frame number. This will flash with a 120*pi frame period.
    //        VkClearValue clearValue = {};
    //        float flash = abs(sin(engine._frameNumber / 3840.f));
    //        clearValue.color = { { 0.0f, 0.0f, flash, 1.0f } };

    //        //start the main renderpass.
    //        //We will use the clear color from above, and the framebuffer of the index the swapchain gave us
    //        VkRenderPassBeginInfo rpInfo = {};
    //        rpInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
    //        rpInfo.pNext = nullptr;

    //        rpInfo.renderPass = engine._renderPass;
    //        rpInfo.renderArea.offset.x = 0;
    //        rpInfo.renderArea.offset.y = 0;
    //        rpInfo.renderArea.extent = engine._windowExtent;
    //        rpInfo.framebuffer = engine._framebuffers[swapchainImageIndex];

    //        //connect clear values
    //        rpInfo.clearValueCount = 1;
    //        rpInfo.pClearValues = &clearValue;

    //        vkCmdBeginRenderPass(cmd, &rpInfo, VK_SUBPASS_CONTENTS_INLINE);

    //       for (auto i : it)
    //       {
    //           Transform transform = transforms[i];
    //           Mesh mesh = meshes[i];
    //           Material material = materials[i];

    //           //vkCmdBindPipeline(cmd, VK_PIPELINE_BIND_POINT_GRAPHICS, material._meshPipeline);

    //           ////bind the mesh vertex buffer with offset 0
    //           //VkDeviceSize offset = 0;
    //           //vkCmdBindVertexBuffers(cmd, 0, 1, &mesh._vertexBuffer._buffer, &offset);

    //           //engine::MeshPushConstants constants = {};
    //           //constants.renderMatrix = mesh.GetRenderMatrix(material);

    //           ////upload the matrix to the GPU via push constants
    //           //vkCmdPushConstants(cmd, _meshPipelineLayout, VK_SHADER_STAGE_VERTEX_BIT, 0, sizeof(MeshPushConstants), &constants);

    //           ////we can now draw the mesh
    //           //vkCmdDraw(cmd, (uint32_t)_triangleMesh._vertices.size(), 1, 0, 0);
    //       }

    //        //finalize the render pass
    //        vkCmdEndRenderPass(cmd);
    //        //finalize the command buffer (we can no longer add commands, but it can now be executed)
    //        VK_CHECK(vkEndCommandBuffer(cmd));


    //        //prepare the submission to the queue.
    //        //we want to wait on the _presentSemaphore, as that semaphore is signaled when the swapchain is ready
    //        //we will signal the _renderSemaphore, to signal that rendering has finished

    //        VkSubmitInfo submit = {};
    //        submit.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
    //        submit.pNext = nullptr;

    //        VkPipelineStageFlags waitStage = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;

    //        submit.pWaitDstStageMask = &waitStage;

    //        submit.waitSemaphoreCount = 1;
    //        submit.pWaitSemaphores = &engine._presentSemaphore;

    //        submit.signalSemaphoreCount = 1;
    //        submit.pSignalSemaphores = &engine._renderSemaphore;

    //        submit.commandBufferCount = 1;
    //        submit.pCommandBuffers = &cmd;

    //        //submit command buffer to the queue and execute it.
    //        // _renderFence will now block until the graphic commands finish execution
    //        VK_CHECK(vkQueueSubmit(engine._graphicsQueue, 1, &submit, engine._renderFence));


    //        // this will put the image we just rendered into the visible window.
    //        // we want to wait on the _renderSemaphore for that,
    //        // as it's necessary that drawing commands have finished before the image is displayed to the user
    //        VkPresentInfoKHR presentInfo = {};
    //        presentInfo.sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR;
    //        presentInfo.pNext = nullptr;

    //        presentInfo.pSwapchains = &engine._swapchain;
    //        presentInfo.swapchainCount = 1;

    //        presentInfo.pWaitSemaphores = &engine._renderSemaphore;
    //        presentInfo.waitSemaphoreCount = 1;

    //        presentInfo.pImageIndices = &swapchainImageIndex;

    //        VK_CHECK(vkQueuePresentKHR(engine._graphicsQueue, &presentInfo));

    //        //increase the number of frames drawn
    //        engine._frameNumber++;
    //   }
    //);
}

void RenderingECS::InitEntities()
{

}

// Private Fields

// Private Methods

glm::mat4 RenderingECS::GetRenderMatrix(const Mesh& mesh, const Material& material)
{
    return glm::mat4(1.0f);
}

} // namespace hh
