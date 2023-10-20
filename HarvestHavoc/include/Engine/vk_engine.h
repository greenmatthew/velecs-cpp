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

    //initializes everything in the engine
    void Init();

    //shuts down the engine
    void Cleanup();

    //run main loop
    void Run();

protected:
    // Protected Fields

    // Protected Methods

private:
    // Private Fields

    bool _isInitialized{false};
    int _frameNumber{0};
    bool isQuitting = false;
    SDL_Event event;

    VkExtent2D _windowExtent{1700, 900};

    struct SDL_Window* _window{nullptr};

    VkInstance _instance; /// \brief Vulkan library handle
    VkDebugUtilsMessengerEXT _debug_messenger; /// \brief Vulkan debug output handle
    VkPhysicalDevice _chosenGPU; /// \brief GPU chosen as the default device
    VkDevice _device; /// \brief Vulkan device for commands
    VkSurfaceKHR _surface; /// \brief Vulkan window surface

    VkSwapchainKHR _swapchain; /// \brief from other articles
    VkFormat _swapchainImageFormat; /// \brief image format expected by the windowing system
    std::vector<VkImage> _swapchainImages; /// \brief array of images from the swapchain
    std::vector<VkImageView> _swapchainImageViews; /// \brief array of image-views from the swapchain

    VkQueue _graphicsQueue; /// \brief queue we will submit to
    uint32_t _graphicsQueueFamily; /// \brief family of that queue
    VkCommandPool _commandPool; /// \brief the command pool for our commands
    VkCommandBuffer _mainCommandBuffer; /// \brief the buffer we will record into

    VkRenderPass _renderPass;
    std::vector<VkFramebuffer> _framebuffers;

    VkSemaphore _presentSemaphore, _renderSemaphore;
	VkFence _renderFence;

    // Private Methods

    void InitVulkan();

    void InitSwapchain();

    void InitCommands();

    void InitDefaultRenderPass();

    void InitFrameBuffers();

    /// \brief create synchronization structures
    void InitSyncStructures();

    void InitInput();

    // input loop
    void InputUpdate();

    //draw loop
    void Draw();
};

} // namespace HarvestHavoc::Engine
