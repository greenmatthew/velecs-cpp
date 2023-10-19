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
	void init();

	//shuts down the engine
	void cleanup();

	//run main loop
	void run();

protected:
    // Protected Fields

    // Protected Methods

private:
    // Private Fields

    bool _isInitialized{false};
	int _frameNumber{0};
    bool isQuitting = false;
    SDL_Event event;
    std::vector<SDL_Keycode> inProcessKeys;

	VkExtent2D _windowExtent{1700, 900};

	struct SDL_Window* _window{nullptr};

    // Private Methods

    // input loop
    void input_update();

	//draw loop
	void draw();
};

} // namespace HarvestHavoc::Engine
