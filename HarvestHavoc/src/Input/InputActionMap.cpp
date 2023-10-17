// -------------------------------------------------------------------------------
// Filename:    InputActionMap.cpp
// Created by:  mgreen
// Created on:  10/16/2023 22:30:21
// -------------------------------------------------------------------------------
// Copyright (c) 2023 Matthew Green - All rights reserved
// Unauthorized copying of this file, via any medium is strictly prohibited
// Proprietary and confidential
// -------------------------------------------------------------------------------

#include "Input/InputActionMap.h"
#include "Input/InputAction.h"
#include "Input/Input.h"

#include <sstream>
// #include <stdexcept>

namespace HarvestHavoc::Input {

// Public Fields

// Constructors and Destructors
InputActionMap::~InputActionMap() = default;

// Public Methods
std::shared_ptr<InputAction> InputActionMap::CreateBinding(const SDL_Keycode keycode)
{
    const auto& it = map.find(keycode);
    if (it == map.end())
    {
        map[keycode] = InputAction::Create(keycode);
    }
    else
    {
        std::ostringstream errMsg;
        errMsg << "[InputActionMap] Duplicate binding. ";
        errMsg << "Name: " << SDL_GetKeyName(keycode) << " ";
        errMsg << "(0x" << std::hex << std::uppercase << keycode << ")";
        
        throw std::runtime_error(errMsg.str());
    }
    
    return map[keycode];
}


void InputActionMap::TryOnPressed(SDL_Keycode keycode)
{
    if (GetIsEnabled())
    {
        auto inputActionPtr = TryFindKeyBind(keycode);
        if (inputActionPtr)
        {
            inputActionPtr->OnPressed.Invoke();
        }
    }
}

void InputActionMap::TryOnHeld(SDL_Keycode keycode)
{
    if (GetIsEnabled())
    {
        auto inputActionPtr = TryFindKeyBind(keycode);
        if (inputActionPtr)
        {
            inputActionPtr->OnHeld.Invoke();
        }
    }
}

void InputActionMap::TryOnReleased(SDL_Keycode keycode)
{
    if (GetIsEnabled())
    {
        auto inputActionPtr = TryFindKeyBind(keycode);
        if (inputActionPtr)
        {
            inputActionPtr->OnReleased.Invoke();
        }        
    }
}

// Protected Fields

// Protected Methods

// Private Fields

// Private Methods
void InputActionMap::ForEachItem(std::function<void(const SDL_Keycode, std::shared_ptr<InputAction>)> callback)
{
    for (auto& [keycode, inputActionPtr] : map)
    {
        callback(keycode, inputActionPtr);
    }
}

std::shared_ptr<InputAction> InputActionMap::TryFindKeyBind(SDL_Keycode keycode) const
{
    auto it = map.find(keycode);
    if (it != map.end())
    {
        return it->second;
    }
    else
    {
        return nullptr;
    }
}

} // namespace HarvestHavoc::Input
