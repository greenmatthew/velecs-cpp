// -------------------------------------------------------------------------------
// Filename:    Input.h
// Created by:  mgreen
// Created on:  10/16/2023 18:30:13
// -------------------------------------------------------------------------------
// Copyright (c) 2023 Matthew Green - All rights reserved
// Unauthorized copying of this file, via any medium is strictly prohibited
// Proprietary and confidential
// -------------------------------------------------------------------------------

#pragma once

#include "IEnableDisable.h"
#include "Input/InputAction.h"
#include "Input/InputActionMap.h"

#include <vector>
#include <unordered_map>
#include <functional>
#include <memory>

#include <SDL2/SDL.h>

namespace HarvestHavoc::Input {

class PlayerInputActionMap;
class MenuInputActionMap;

/// <summary>
/// Summary of class
/// </summary>
class Input : public IEnableDisable {
public:
    // Enums

    // Public Fields
    std::shared_ptr<PlayerInputActionMap> Player;
    std::shared_ptr<MenuInputActionMap> Menu;

    // Deleted copy constructor and assignment operator
    Input(const Input&) = delete;
    Input& operator=(const Input&) = delete;

    // Public Methods
    static Input& GetInstance() {
        static Input instance;  // Created on first use, destroyed at program end
        return instance;
    }

    void Init();

    template<typename T>
    std::shared_ptr<T> CreateMap()
    {
        static_assert(std::is_base_of<InputActionMap, T>::value, "[Input] T must be a subclass of InputActionMap.");
        auto inputActionMapPtr = std::make_shared<T>();
        inputActionMapPtr->Init();
        maps.push_back(inputActionMapPtr);
        return inputActionMapPtr;
    }

    //std::shared_ptr<InputAction> CreateBinding(const SDL_Keycode keycode);

    void TryOnPressed(const SDL_Keycode keycode);
    void TryOnHeld();
    void TryOnReleased(const SDL_Keycode keycode);

protected:
    // Protected Fields

    // Protected Methods

private:
    // Private Fields
    std::vector<std::shared_ptr<InputActionMap>> maps = std::vector<std::shared_ptr<InputActionMap>>();
    std::unordered_map<SDL_Keycode, std::vector<std::shared_ptr<InputAction>>> keyBinds = std::unordered_map<SDL_Keycode, std::vector<std::shared_ptr<InputAction>>>();

    // Private Methods

    // Constructors and Deconstructor
    Input() = default;
    ~Input() = default;

    void ForEachMap(std::function<void(std::shared_ptr<InputActionMap>)> callback);
    void ForEachKeyBinding(std::function<void(const SDL_Keycode, std::shared_ptr<InputAction>)> callback);
};

} // namespace HarvestHavoc::Input
