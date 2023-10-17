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
    const auto& it = keyBinds.find(keycode);
    if (it == keyBinds.end())
    {
        keyBinds[keycode] = InputAction::Create(keycode);
    }
    else
    {
        std::ostringstream errMsg;
        errMsg << "[InputActionMap] Duplicate binding. ";
        errMsg << "Name: " << SDL_GetKeyName(keycode) << " ";
        errMsg << "(0x" << std::hex << std::uppercase << keycode << ")";
        
        throw std::runtime_error(errMsg.str());
    }
    
    return keyBinds[keycode];
}


void InputActionMap::TryOnPressed(const SDL_Keycode keycode)
{
    if (GetIsEnabled())
    {
        auto inputActionPtr = TryFindKeyBind(keycode);
        if (inputActionPtr)
        {
            inputActionPtr->TryInvokeOnPressed();
        }
    }
}

void InputActionMap::TryOnHeld()
{
    if (GetIsEnabled())
    {
        // auto inputActionPtr = TryFindKeyBind(keycode);
        // if (inputActionPtr)
        // {
        //     inputActionPtr->TryInvokeOnHeld();
        // }
    }
}

void InputActionMap::TryOnReleased(const SDL_Keycode keycode)
{
    if (GetIsEnabled())
    {
        auto inputActionPtr = TryFindKeyBind(keycode);
        if (inputActionPtr)
        {
            inputActionPtr->TryInvokeOnReleased();
        }        
    }
}

// Protected Fields

// Protected Methods

// Private Fields

// Private Methods
void InputActionMap::ForEachItem(std::function<void(const SDL_Keycode, std::shared_ptr<InputAction>)> callback)
{
    for (auto& [keycode, inputActionPtr] : keyBinds)
    {
        callback(keycode, inputActionPtr);
    }
}

std::shared_ptr<InputAction> InputActionMap::TryFindKeyBind(SDL_Keycode keycode) const
{
    auto it = keyBinds.find(keycode);
    if (it != keyBinds.end())
    {
        return it->second;
    }
    else
    {
        return nullptr;
    }
}

} // namespace HarvestHavoc::Input
