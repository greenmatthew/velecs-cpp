// -------------------------------------------------------------------------------
// Filename:    Input.cpp
// Created by:  mgreen
// Created on:  10/16/2023 18:36:19
// -------------------------------------------------------------------------------
// Copyright (c) 2023 Matthew Green - All rights reserved
// Unauthorized copying of this file, via any medium is strictly prohibited
// Proprietary and confidential
// -------------------------------------------------------------------------------

#include "Input/Input.h"
#include "Input/InputActionMap.h"
#include "Input/InputAction.h"
#include "Input/PlayerInputActionMap.h"
#include "Input/MenuInputActionMap.h"

namespace HarvestHavoc::Input {

// Public Fields

// Public Methods
void Input::Init()
{
    Player = CreateMap<PlayerInputActionMap>();
    Menu = CreateMap<MenuInputActionMap>();
}

//std::shared_ptr<InputAction> Input::CreateBinding(const SDL_Keycode keycode)
//{
//    auto it = keyBinds.find(keycode);
//    if (it != keyBinds.end())
//    {
//        // Keycode already exists, add a new InputAction to the vector
//        it->second.push_back(InputAction::Create(keycode));
//        return it->second.back();
//    }
//    else
//    {
//        // Keycode does not exist, create a new vector and add it to the map
//        std::vector<std::shared_ptr<InputAction>> newVector;
//        newVector.push_back(InputAction::Create(keycode));
//        auto [newIt, inserted] = keyBinds.emplace(keycode, std::move(newVector));
//        if (!inserted)
//        {
//            throw std::runtime_error("Failed to insert new binding");  // This should never happen
//        }
//        return newIt->second.back();
//    }
//}

void Input::TryOnPressed(const SDL_Keycode keycode)
{
    if (GetIsEnabled())
    {
        ForEachMap([keycode](std::shared_ptr<InputActionMap> inputActionMapPtr) { inputActionMapPtr->TryOnPressed(keycode); });
    }
}
void Input::TryOnHeld()
{
    if (GetIsEnabled())
    {
        ForEachMap([](std::shared_ptr<InputActionMap> inputActionMapPtr) { inputActionMapPtr->TryOnHeld(); });
    }
}
void Input::TryOnReleased(const SDL_Keycode keycode)
{
    if (GetIsEnabled())
    {
        ForEachMap([keycode](std::shared_ptr<InputActionMap> inputActionMapPtr) { inputActionMapPtr->TryOnReleased(keycode); });
    }
}

// Protected Fields

// Protected Methods

// Private Fields
void Input::ForEachMap(std::function<void(std::shared_ptr<InputActionMap>)> callback)
{
    for (auto& map : maps)
    {
        callback(map);
    }
}

void Input::ForEachKeyBinding(std::function<void(const SDL_Keycode, std::shared_ptr<InputAction>)> callback)
{
    for (auto& [keycode, inputActionPtrs] : keyBinds)
    {
        for (auto& inputActionPtr : inputActionPtrs)
        {
            callback(keycode, inputActionPtr);
        }
    }
}

// Private Methods

} // namespace HarvestHavoc::Input
