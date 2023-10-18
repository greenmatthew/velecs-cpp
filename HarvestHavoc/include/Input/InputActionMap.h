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
#include "Input/IInputAccessor.h"

#include <memory>
#include <unordered_map>
#include <functional>

#include <SDL2/SDL.h>

namespace HarvestHavoc::Input {

class InputAction;

/// <summary>
/// Summary of class
/// </summary>
class InputActionMap : public IEnableDisable, public IInputAccessor {
public:
    // Enums

    // Public Fields

    // Constructors and Destructors
    InputActionMap();
    virtual ~InputActionMap() = 0;

    // Public Methods
    virtual void Init() = 0;

    std::shared_ptr<InputAction> CreateBinding(const SDL_Keycode keycode);

    bool TryOnPressed(const SDL_Keycode keycode);
    bool TryOnHeld();
    bool TryOnReleased(const SDL_Keycode keycode);
    void TrySettingToIdle();

    void AddToHeldKeyBinds(std::shared_ptr<InputAction>);
    void RemoveFromHeldKeyBinds(std::shared_ptr<InputAction>);
    void AddToReleasedKeyBinds(std::shared_ptr<InputAction>);
    void RemoveFromReleasedKeyBinds(std::shared_ptr<InputAction>);

    void OnEnable() override;
    void OnDisable() override;

    virtual void Switch() = 0;

protected:
    // Protected Fields

    // Protected Methods

private:
    // Private Fields
    std::unordered_map<SDL_Keycode, std::shared_ptr<InputAction>> keyBinds = std::unordered_map<SDL_Keycode, std::shared_ptr<InputAction>>();
    std::vector<std::shared_ptr<InputAction>> heldKeyBinds = std::vector<std::shared_ptr<InputAction>>();
    std::vector<std::shared_ptr<InputAction>> releasedKeyBinds = std::vector<std::shared_ptr<InputAction>>();

    bool isEnabled = true;

    // Private Methods
    void ForEachKeyBind(std::function<void(const SDL_Keycode, std::shared_ptr<InputAction>)> callback);
    void ForEachHeldKeyBind(std::function<void(std::shared_ptr<InputAction>)> callback);
    void ForEachReleasedKeyBind(std::function<void(std::shared_ptr<InputAction>)> callback);

    std::shared_ptr<InputAction> TryFindKeyBind(const SDL_Keycode keycode) const;
};

} // namespace HarvestHavoc::Input
