// -------------------------------------------------------------------------------
// Filename:    PlayerInputActionMap.cpp
// Created by:  mgreen
// Created on:  10/16/2023 18:51:33
// -------------------------------------------------------------------------------
// Copyright (c) 2023 Matthew Green - All rights reserved
// Unauthorized copying of this file, via any medium is strictly prohibited
// Proprietary and confidential
// -------------------------------------------------------------------------------

#include "Input/PlayerInputActionMap.h"
#include "Input/InputActionMap.h"
#include "Input/InputAction.h"

#include <iostream>

#include "SDL2/SDL.h"

namespace HarvestHavoc::Input {

// Public Fields

// Constructors and Destructors

// Public Methods
void GoLeft()
{
    std::cout << SDL_GetKeyName(SDLK_LEFT) << std::endl;
}

void GoRight()
{
    std::cout << SDL_GetKeyName(SDLK_RIGHT) << std::endl;
}

void Test()
{
    std::cout << "TEST" << std::endl;
}

void PlayerInputActionMap::Init()
{
    LeftStrafe = CreateBinding(SDLK_LEFT);
    LeftStrafe->OnPressed.AddListener(GoLeft);
    LeftStrafe->OnReleased.AddListener(Test);
    RightStrafe = CreateBinding(SDLK_RIGHT);
    RightStrafe->OnPressed.AddListener(GoRight);
}

// Protected Fields

// Protected Methods

// Private Fields

// Private Methods

} // namespace HarvestHavoc::Input
