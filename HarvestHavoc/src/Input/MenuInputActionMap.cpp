// -------------------------------------------------------------------------------
// Filename:    MenuInputActionMap.cpp
// Created by:  mgreen
// Created on:  10/16/2023 18:51:43
// -------------------------------------------------------------------------------
// Copyright (c) 2023 Matthew Green - All rights reserved
// Unauthorized copying of this file, via any medium is strictly prohibited
// Proprietary and confidential
// -------------------------------------------------------------------------------

#include "Input/MenuInputActionMap.h"
#include "Input/InputActionMap.h"
#include "Input/InputAction.h"
#include "Input/Input.h"

#include <iostream>

#include "SDL2/SDL.h"

namespace HarvestHavoc::Input {

// Public Fields

// Constructors and Destructors

// Public Methods
void CloseMenu()
{
    std::cout << "Closing menu." << std::endl;
    Input::GetInstance().Player->Switch();
}

void MenuInputActionMap::Init()
{
    Escape = CreateBinding(SDLK_ESCAPE);
    Escape->OnPressed += CloseMenu;
}

void MenuInputActionMap::Switch()
{
    input.SwitchTo(input.Menu);
}

// Protected Fields

// Protected Methods

// Private Fields

// Private Methods

} // namespace HarvestHavoc::Input
