// -------------------------------------------------------------------------------
// Filename:    InputAction.h
// Created by:  mgreen
// Created on:  10/16/2023 19:45:08
// -------------------------------------------------------------------------------
// Copyright (c) 2023 Matthew Green - All rights reserved
// Unauthorized copying of this file, via any medium is strictly prohibited
// Proprietary and confidential
// -------------------------------------------------------------------------------

#pragma once

#include "IEnableDisable.h"
#include "Input/Event.h"

#include <memory>

#include <SDL2/SDL.h>

namespace HarvestHavoc::Input {

enum class ButtonState
{
    Idle,
    Pressed,
    Held,
    Released,
};

/// <summary>
/// Summary of class
/// </summary>
class InputAction : public IEnableDisable {
public:
    // Friends
    // friend class Input;

    // Enums

    // Public Fields
    Event<> OnPressed;
    Event<> OnHeld;
    Event<> OnReleased;

    // Destructors
    InputAction(SDL_Keycode keycode);
    ~InputAction() = default;

    // Public Methods
    static std::shared_ptr<InputAction> Create(const SDL_Keycode keycode);

    void TryInvokeOnPressed();
    void TryInvokeOnHeld();
    void TryInvokeOnReleased();

protected:
    // Protected Fields

    // Protected Methods

private:
    // Private Fields
    const SDL_Keycode keycode;
    ButtonState state = ButtonState::Idle;

    // Constructors
    

    // Private Methods
};

} // namespace HarvestHavoc::Input
