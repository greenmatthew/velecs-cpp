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

#include <iostream>
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

void InputAction::TryInvokeOnPressed()
{
    switch (state)
    {
        case ButtonState::Idle:
        case ButtonState::Released:
            state = ButtonState::Pressed;
            std::cout << "Key pressed: " << SDL_GetKeyName(keycode) << " (0x" << std::hex << std::uppercase << keycode << ')' << std::endl;
            OnPressed.Invoke();
            break;
        case ButtonState::Pressed:
            break; // Ignore as SDL repeats KEYDOWN events
        case ButtonState::Held:
        default:
            throw std::logic_error("[InputAction] Attempt to invoke OnPressed while in an invalid state (either Pressed, Held, or some unknown state).");
    }
}

void InputAction::TryInvokeOnHeld()
{
    switch (state)
    {
        case ButtonState::Pressed:
            state = ButtonState::Held;
            [[fallthrough]];
        case ButtonState::Held:
            std::cout << "Key is held: " << SDL_GetKeyName(keycode) << " (0x" << std::hex << std::uppercase << keycode << ')' << std::endl;
            OnHeld.Invoke();
            break;
        case ButtonState::Idle:
        case ButtonState::Released:
        default:
            throw std::logic_error("[InputAction] Attempt to invoke OnHeld while in an invalid state (either Idle, Released, or some unknown state).");
    }
}

void InputAction::TryInvokeOnReleased()
{
    switch (state)
    {
        case ButtonState::Pressed:
        case ButtonState::Held:
            state = ButtonState::Released;
            std::cout << "Key released: " << SDL_GetKeyName(keycode) << " (0x" << std::hex << std::uppercase << keycode << ')' << std::endl;
            OnReleased.Invoke();
            break;
        case ButtonState::Idle:
        case ButtonState::Released:
        default:
            throw std::logic_error("[InputAction] Attempt to invoke OnReleased while in an invalid state (either Idle, Released, or some unknown state).");
    }
}


// Protected Fields

// Protected Methods

// Private Fields

// Constructors
InputAction::InputAction(SDL_Keycode keycode) : keycode(keycode) {}

// Private Methods

} // namespace HarvestHavoc::Input
