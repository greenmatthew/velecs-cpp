/// \file    InputActionMap.cpp
/// \author  Matthew Green
/// \date    10/16/2023 22:30:21
/// 
/// \section LICENSE
/// 
/// Copyright (c) 2023 Matthew Green - All rights reserved
/// Unauthorized copying of this file, via any medium is strictly prohibited
/// Proprietary and confidential

#include "Input/InputActionMap.h"
#include "Input/InputAction.h"
#include "Input/Input.h"

#include <sstream>
#include <algorithm>

namespace engine {

// Public Fields

// Constructors and Destructors

InputActionMap::InputActionMap()
{
    heldKeyBinds.reserve(10);
    releasedKeyBinds.reserve(10);
}

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


bool InputActionMap::TryOnPressed(const SDL_Keycode keycode)
{
    if (GetIsEnabled())
    {
        auto inputActionPtr = TryFindKeyBind(keycode);
        if (inputActionPtr)
        {
            if (inputActionPtr->TryInvokeOnPressed())
            {
                AddToHeldKeyBinds(inputActionPtr);
                return true;
            }
        }
    }
    return false;
}

bool InputActionMap::TryOnHeld()
{
    bool result = false;
    if (GetIsEnabled())
    {
        if (!heldKeyBinds.empty())
        {
            ForEachHeldKeyBind
            (
                [&](std::shared_ptr<InputAction> inputActionPtr)
                { 
                    if (inputActionPtr->TryInvokeOnHeld())
                    {
                        result = true;
                    }
                }
            );
        }
    }
    return result;
}

bool InputActionMap::TryOnReleased(const SDL_Keycode keycode)
{
    if (GetIsEnabled())
    {
        auto inputActionPtr = TryFindKeyBind(keycode);
        if (inputActionPtr)
        {
            if (inputActionPtr->TryInvokeOnReleased())
            {
                RemoveFromHeldKeyBinds(inputActionPtr);
                AddToReleasedKeyBinds(inputActionPtr);
                return true;
            }
        }        
    }
    return false;
}

void InputActionMap::TrySettingToIdle()
{
    if (GetIsEnabled())
    {
        if (!releasedKeyBinds.empty())
        {
            ForEachReleasedKeyBind
            (
                [&](std::shared_ptr<InputAction> inputActionPtr)
                {
                    RemoveFromReleasedKeyBinds(inputActionPtr);
                    inputActionPtr->SetStateToIdle();
                }
            );

            // Clear the vector afterwards
            releasedKeyBinds.clear();
        }
    }
}

void InputActionMap::AddToHeldKeyBinds(std::shared_ptr<InputAction> inputActionPtr)
{
    heldKeyBinds.push_back(inputActionPtr);
}

void InputActionMap::RemoveFromHeldKeyBinds(std::shared_ptr<InputAction> inputActionPtr)
{
    heldKeyBinds.erase(
        std::remove(heldKeyBinds.begin(), heldKeyBinds.end(), inputActionPtr),
        heldKeyBinds.end()
    );
}

void InputActionMap::AddToReleasedKeyBinds(std::shared_ptr<InputAction> inputActionPtr)
{
    releasedKeyBinds.push_back(inputActionPtr);
}

void InputActionMap::RemoveFromReleasedKeyBinds(std::shared_ptr<InputAction> inputActionPtr)
{
    releasedKeyBinds.erase(
        std::remove(releasedKeyBinds.begin(), releasedKeyBinds.end(), inputActionPtr),
        releasedKeyBinds.end()
    );
}

void InputActionMap::OnEnable()
{
    ForEachKeyBind([](const SDL_Keycode keycode, std::shared_ptr<InputAction> inputActionPtr) { inputActionPtr->SetStateToIdle(); });
}

void InputActionMap::OnDisable()
{
    ForEachKeyBind([](const SDL_Keycode keycode, std::shared_ptr<InputAction> inputActionPtr) { inputActionPtr->SetStateToDisabled(); });
}

// Protected Fields

// Protected Methods

// Private Fields

// Private Methods
void InputActionMap::ForEachKeyBind(std::function<void(const SDL_Keycode, std::shared_ptr<InputAction>)> callback)
{
    for (auto& [keycode, inputActionPtr] : keyBinds)
    {
        callback(keycode, inputActionPtr);
    }
}

void InputActionMap::ForEachHeldKeyBind(std::function<void(std::shared_ptr<InputAction>)> callback)
{
    for (auto& inputActionPtr : heldKeyBinds)
    {
        callback(inputActionPtr);
    }
}

void InputActionMap::ForEachReleasedKeyBind(std::function<void(std::shared_ptr<InputAction>)> callback)
{
    for (auto& inputActionPtr : releasedKeyBinds)
    {
        callback(inputActionPtr);
    }
}

std::shared_ptr<InputAction> InputActionMap::TryFindKeyBind(const SDL_Keycode keycode) const
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

} // namespace engine
