/// \file    PlayerInputActionMap.cpp
/// \author  Matthew Green
/// \date    10/16/2023 18:51:33
/// 
/// \section LICENSE
/// 
/// Copyright (c) 2023 Matthew Green - All rights reserved
/// Unauthorized copying of this file, via any medium is strictly prohibited
/// Proprietary and confidential

#include "Input/PlayerInputActionMap.h"
#include "Input/InputActionMap.h"
#include "Input/InputAction.h"
#include "Input/Input.h"

#include <iostream>

#include "SDL2/SDL.h"

namespace HarvestHavoc::Input {

// Public Fields

// Constructors and Destructors

// Public Methods

void OpenMenu()
{
    std::cout << "Opening menu." << std::endl;
    Input::GetInstance().Menu->Switch();
}

void StartGoingLeft()
{
    std::cout << "Started going left." << std::endl;
}

void StopGoingLeft()
{
    std::cout << "Stopped going left." << std::endl;
}

void StartGoingRight()
{
    std::cout << "Started going right." << std::endl;
}

void StopGoingRight()
{
    std::cout << "Stopped going right." << std::endl;
}

void PlayerInputActionMap::Init()
{
    Escape = CreateBinding(SDLK_ESCAPE);
    Escape->OnPressed += OpenMenu;

    LeftStrafe = CreateBinding(SDLK_LEFT);
    LeftStrafe->OnPressed += StartGoingLeft;
    LeftStrafe->OnReleased += StopGoingLeft;
    
    RightStrafe = CreateBinding(SDLK_RIGHT);
    RightStrafe->OnPressed += StartGoingRight;
    RightStrafe->OnReleased += StopGoingRight;
}

void PlayerInputActionMap::Switch()
{
    input.SwitchTo(input.Player);
}

// Protected Fields

// Protected Methods

// Private Fields

// Private Methods

} // namespace HarvestHavoc::Input
