// -------------------------------------------------------------------------------
// Filename:    InputActionMap.h
// Created by:  mgreen
// Created on:  10/16/2023 19:08:09
// -------------------------------------------------------------------------------
// Copyright (c) 2023 Matthew Green - All rights reserved
// Unauthorized copying of this file, via any medium is strictly prohibited
// Proprietary and confidential
// -------------------------------------------------------------------------------

#pragma once

#include "IEnableDisable.h"

#include <memory>
#include <unordered_map>
#include <functional>

#include <SDL2/SDL.h>

namespace HarvestHavoc::Input {

class InputAction;

/// <summary>
/// Summary of class
/// </summary>
class InputActionMap : public IEnableDisable {
public:
    // Enums

    // Public Fields

    // Constructors and Destructors
    InputActionMap() = default;
    virtual ~InputActionMap() = 0;

    // Public Methods
    virtual void Init() = 0;

    std::shared_ptr<InputAction> CreateBinding(const SDL_Keycode keycode);

    void TryOnPressed(SDL_Keycode keycode);
    void TryOnHeld(SDL_Keycode keycode);
    void TryOnReleased(SDL_Keycode keycode);

protected:
    // Protected Fields

    // Protected Methods

private:
    // Private Fields
    std::unordered_map<SDL_Keycode, std::shared_ptr<InputAction>> map = std::unordered_map<SDL_Keycode, std::shared_ptr<InputAction>>();

    bool isEnabled = true;

    // Private Methods
    void ForEachItem(std::function<void(const SDL_Keycode, std::shared_ptr<InputAction>)> callback);

    std::shared_ptr<InputAction> TryFindKeyBind(SDL_Keycode keycode) const;
};

} // namespace HarvestHavoc::Input
