/// @file    Input.cpp
/// @author  Matthew Green
/// @date    2023-11-13 15:05:46
/// 
/// @section LICENSE
/// 
/// Copyright (c) 2023 Matthew Green - All rights reserved
/// Unauthorized copying of this file, via any medium is strictly prohibited
/// Proprietary and confidential

#include "ECS/Components/Input.h"

namespace hh {

// Public Fields

// Constructors and Destructors

// Public Methods

Input::State Input::GetState(const SDL_Keycode keycode) const
{
    auto prevIt = prevKeyFlags.find(keycode);
    bool prevFlag = (prevIt != prevKeyFlags.end()) ? prevIt->second : false;

    auto currIt = currKeyFlags.find(keycode);
    bool currFlag = (currIt != currKeyFlags.end()) ? currIt->second : false;

    if (!prevFlag && currFlag)
    {
        return State::Pressed;
    }
    else if (prevFlag && currFlag)
    {
        return State::Held;
    }
    else if (prevFlag && !currFlag)
    {
        return State::Released;
    }
    else
    {
        return State::Idle;
    }
}

bool Input::IsPressed(const SDL_Keycode keycode) const
{
    return GetState(keycode) == State::Pressed;
}

bool Input::IsHeld(const SDL_Keycode keycode) const
{
    return GetState(keycode) == State::Held;
}

bool Input::IsIdle(const SDL_Keycode keycode) const
{
    return GetState(keycode) == State::Idle;
}

// Protected Fields

// Protected Methods

// Private Fields

// Private Methods

} // namespace hh
