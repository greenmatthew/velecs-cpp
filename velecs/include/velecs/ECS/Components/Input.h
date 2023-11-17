/// @file    Input.h
/// @author  Matthew Green
/// @date    2023-11-13 13:22:42
/// 
/// @section LICENSE
/// 
/// Copyright (c) 2023 Matthew Green - All rights reserved
/// Unauthorized copying of this file, via any medium is strictly prohibited
/// Proprietary and confidential

#pragma once

#include "velecs/Math/Vec2.h"

#include <SDL2/SDL.h>

#include <unordered_map>

namespace velecs {

/// @struct Input
/// @brief Manages the input state for SDL_Keycode keys.
///
/// This class provides functionality to check the state of keys (Idle, Pressed, Held, Released)
/// during the game loop. It keeps track of the previous and current state of keys to determine
/// their state in the current frame.
struct Input {
    /// @enum State
    /// @brief Represents the state of a key.
    ///
    /// The state can be Idle (not active), Pressed (activated this frame),
    /// Held (continuously active), or Released (deactivated this frame).
    enum class State
    {
        Idle = 0,
        Pressed,
        Held,
        Released
    };

    bool isQuitting = false; /// @brief Flag to indicate if the game is quitting.
    std::unordered_map<SDL_Keycode, bool> prevKeyFlags; /// @brief Stores the previous frame's key states.
    std::unordered_map<SDL_Keycode, bool> currKeyFlags; /// @brief Stores the current frame's key states.
    Vec2 mouseWheel = Vec2::zero();

    /// @brief Gets the state of a specific key.
    /// @param[in] keycode The SDL_Keycode for the key being checked.
    /// @return The state of the key (Idle, Pressed, Held, Released).
    State GetState(const SDL_Keycode keycode) const;

    /// @brief Checks if a key was pressed in the current frame.
    /// @param[in] keycode The SDL_Keycode for the key being checked.
    /// @return True if the key was pressed, false otherwise.
    bool IsPressed(const SDL_Keycode keycode) const;

    /// @brief Checks if a key is being held down.
    /// @param[in] keycode The SDL_Keycode for the key being checked.
    /// @return True if the key is held, false otherwise.
    bool IsHeld(const SDL_Keycode keycode) const;

    /// @brief Checks if a key is idle in the current frame.
    /// @param[in] keycode The SDL_Keycode for the key being checked.
    /// @return True if the key is idle, false otherwise.
    bool IsIdle(const SDL_Keycode keycode) const;
};

} // namespace velecs
