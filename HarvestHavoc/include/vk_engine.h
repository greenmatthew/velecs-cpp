// vulkan_guide.h : Include file for standard system include files,
// or project specific include files.

#pragma once

#include <vk_types.h>

#include <vector>

#include <SDL2/SDL.h>

class VulkanEngine {
public:

	bool _isInitialized{ false };
	int _frameNumber {0};
    bool isQuitting = false;
    SDL_Event event;
    std::vector<SDL_Keycode> inProcessKeys;

	VkExtent2D _windowExtent{ 1700 , 900 };

	struct SDL_Window* _window{ nullptr };

	//initializes everything in the engine
	void init();

	//shuts down the engine
	void cleanup();

    // input loop
    void input_update();

	//draw loop
	void draw();

	//run main loop
	void run();
};
