/// \file    Input.cpp
/// \author  Matthew Green
/// \date    10/16/2023 18:36:19
/// 
/// \section LICENSE
/// 
/// Copyright (c) 2023 Matthew Green - All rights reserved
/// Unauthorized copying of this file, via any medium is strictly prohibited
/// Proprietary and confidential

#include "Input/Input.h"
#include "Input/InputActionMap.h"
#include "Input/InputAction.h"
#include "Input/PlayerInputActionMap.h"
#include "Input/MenuInputActionMap.h"
#include "Input/IEnableDisablePassKey.h"

namespace engine::Input {

// Public Fields

// Public Methods

bool IInput::TryOnPressed(const SDL_Keycode keycode)
{
    bool result = false;
    if (GetIsEnabled())
    {
        ForEachMap
        (
            [&result, keycode](std::shared_ptr<InputActionMap> inputActionMapPtr)
            {
                if (inputActionMapPtr->TryOnPressed(keycode))
                {
                    result = true;
                }
            }
        );
    }
    return result;
}

bool IInput::TryOnHeld()
{
    bool result = false;
    if (GetIsEnabled())
    {
        ForEachMap
        (
            [&result](std::shared_ptr<InputActionMap> inputActionMapPtr)
            {
                if (inputActionMapPtr->TryOnHeld())
                {
                    result = true;
                }
            }
        );
    }
    return result;
}

bool IInput::TryOnReleased(const SDL_Keycode keycode)
{
    bool result = false;
    if (GetIsEnabled())
    {
        ForEachMap
        (
            [&result, keycode](std::shared_ptr<InputActionMap> inputActionMapPtr)
            {
                if (inputActionMapPtr->TryOnReleased(keycode))
                {
                    result = true;
                }
            }
        );
    }
    return result;
}

void IInput::TrySettingToIdle()
{
    if (GetIsEnabled())
    {
        ForEachMap([](std::shared_ptr<InputActionMap> inputActionMapPtr) { inputActionMapPtr->TrySettingToIdle(); });
    }
}

void IInput::HandleIEnableDisableRequests()
{
    ForEachMap
    (
        [&](std::shared_ptr<InputActionMap> inputActionMapPtr)
        {
            HandleIEnableDisableRequests(inputActionMapPtr);
        }
    );

    ForEachKeyBinding
    (
        [&](const SDL_Keycode keycode, std::shared_ptr<InputAction> inputActionPtr)
        {
            HandleIEnableDisableRequests(inputActionPtr);
        }
    );
}

// Protected Fields

// Protected Methods

void IInput::InternalSwitchTo(std::shared_ptr<InputActionMap> inputActionMapPtr)
{
    ForEachMap([](std::shared_ptr<InputActionMap> inputActionMapPtr) { inputActionMapPtr->RequestDisable(); });
    inputActionMapPtr->RequestEnable();
}

// Private Fields

std::vector<std::shared_ptr<InputActionMap>> IInput::maps = std::vector<std::shared_ptr<InputActionMap>>();
std::unordered_map<SDL_Keycode, std::vector<std::shared_ptr<InputAction>>> IInput::keyBinds = std::unordered_map<SDL_Keycode, std::vector<std::shared_ptr<InputAction>>>();

// Private Methods

void IInput::ForEachMap(std::function<void(std::shared_ptr<InputActionMap>)> callback)
{
    for (auto& map : maps)
    {
        callback(map);
    }
}

void IInput::ForEachKeyBinding(std::function<void(const SDL_Keycode, std::shared_ptr<InputAction>)> callback)
{
    for (auto& [keycode, inputActionPtrs] : keyBinds)
    {
        for (auto& inputActionPtr : inputActionPtrs)
        {
            callback(keycode, inputActionPtr);
        }
    }
}

void IInput::HandleIEnableDisableRequests(std::shared_ptr<IEnableDisable> object)
{
    object->HandleRequests(IEnableDisablePassKey{});
}

} // namespace engine::Input
