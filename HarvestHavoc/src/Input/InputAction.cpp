// -------------------------------------------------------------------------------
// Filename:    InputAction.cpp
// Created by:  mgreen
// Created on:  10/16/2023 19:45:16
// -------------------------------------------------------------------------------
// Copyright (c) 2023 Matthew Green - All rights reserved
// Unauthorized copying of this file, via any medium is strictly prohibited
// Proprietary and confidential
// -------------------------------------------------------------------------------

#include "Input/InputAction.h"
#include "Input/Input.h"

#include <stdexcept>

namespace HarvestHavoc::Input {

// Public Fields

// Destructors

// Public Methods
std::shared_ptr<InputAction> InputAction::Create(const SDL_Keycode keycode)
{
    auto inputActionPtr = std::make_shared<InputAction>(keycode);
    return inputActionPtr;
}

// Protected Fields

// Protected Methods

// Private Fields

// Constructors
InputAction::InputAction(SDL_Keycode keycode) : keycode(keycode) {}

// Private Methods

} // namespace HarvestHavoc::Input
