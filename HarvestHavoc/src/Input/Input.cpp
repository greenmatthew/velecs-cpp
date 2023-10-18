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
#include "Input/IEnableDisablePassKey.h"

namespace HarvestHavoc::Input {

// Public Fields

// Public Methods
void Input::Init()
{
    Player = CreateMap<PlayerInputActionMap>();
    Menu = CreateMap<MenuInputActionMap>();
}

bool Input::TryOnPressed(const SDL_Keycode keycode)
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

bool Input::TryOnHeld()
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

bool Input::TryOnReleased(const SDL_Keycode keycode)
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

void Input::TrySettingToIdle()
{
    if (GetIsEnabled())
    {
        ForEachMap([](std::shared_ptr<InputActionMap> inputActionMapPtr) { inputActionMapPtr->TrySettingToIdle(); });
    }
}

void Input::SwitchTo(std::shared_ptr<InputActionMap> inputActionMapPtr)
{
    ForEachMap([](std::shared_ptr<InputActionMap> inputActionMapPtr) { inputActionMapPtr->RequestDisable(); });
    inputActionMapPtr->RequestEnable();
}

void Input::HandleIEnableDisableRequests()
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

// Private Fields

// Private Methods
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

void Input::HandleIEnableDisableRequests(std::shared_ptr<IEnableDisable> object)
{
    object->HandleRequests(IEnableDisablePassKey{});
}

} // namespace HarvestHavoc::Input
