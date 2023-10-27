/// \file    InputAction.cpp
/// \author  Matthew Green
/// \date    10/16/2023 19:45:16
/// 
/// \section LICENSE
/// 
/// Copyright (c) 2023 Matthew Green - All rights reserved
/// Unauthorized copying of this file, via any medium is strictly prohibited
/// Proprietary and confidential

#include "Debug.h"

#ifdef DEBUG_MODE
    #include <iostream>
#endif

#include "Input/InputAction.h"
#include "Input/Input.h"

#include <stdexcept>
#include <memory>
#include <sstream>

namespace engine::Input {

std::ostream& operator<<(std::ostream& os, const ButtonState& state) {
    switch (state) {
    case ButtonState::Idle: os << "Idle"; break;
    case ButtonState::Pressed: os << "Pressed"; break;
    case ButtonState::Held: os << "Held"; break;
    case ButtonState::Released: os << "Released"; break;
    case ButtonState::Disabled: os << "Disabled"; break;
    default: os.setstate(std::ios_base::failbit); break;  // Optional: mark the stream as failed if an unknown enum value is encountered
    }
    return os;
}

// Public Fields

// Destructors

// Public Methods

std::shared_ptr<InputAction> InputAction::Create(const SDL_Keycode keycode)
{
    auto inputActionPtr = std::make_shared<InputAction>(keycode);
    return inputActionPtr;
}

bool InputAction::TryInvokeOnPressed()
{
    switch (state)
    {
        case ButtonState::Idle:
        case ButtonState::Released:
            state = ButtonState::Pressed;
#ifdef DEBUG_INPUTACTION
            std::cout << "Key pressed: " << SDL_GetKeyName(keycode) << " (0x" << std::hex << std::uppercase << keycode << ')' << std::endl;
#endif
            OnPressed.Invoke();
            return true;
        case ButtonState::Held:
        case ButtonState::Pressed:
        case ButtonState::Disabled:
            return false; // Ignore as SDL repeats KEYDOWN events also ignore when disabled.
        default:
            std::ostringstream errMsg;
            errMsg << "[InputAction] Attempt to invoke OnPressed while in an invalid state (either Pressed, Held, or some unknown state): " << state;
            throw std::logic_error(errMsg.str());
            return false;
    }
}

bool InputAction::TryInvokeOnHeld()
{
    switch (state)
    {
        case ButtonState::Pressed:
            state = ButtonState::Held;
            [[fallthrough]];
        case ButtonState::Held:
#ifdef DEBUG_INPUTACTION_HELD
            std::cout << "Key is held: " << SDL_GetKeyName(keycode) << " (0x" << std::hex << std::uppercase << keycode << ')' << std::endl;
#endif
            OnHeld.Invoke();
            return true;
        case ButtonState::Idle:
        case ButtonState::Disabled:
            return false; // Ignore when disabled or idle (idle means it was just enabled, and we want to discard all left over held and released events)
        case ButtonState::Released:
        default:
            std::ostringstream errMsg;
            errMsg << "[InputAction] Attempt to invoke OnHeld while in an invalid state (either Idle, Released, or some unknown state): " << state;
            throw std::logic_error(errMsg.str());
    }
}

bool InputAction::TryInvokeOnReleased()
{
    switch (state)
    {
        case ButtonState::Pressed:
        case ButtonState::Held:
            state = ButtonState::Released;
#ifdef DEBUG_INPUTACTION
            std::cout << "Key released: " << SDL_GetKeyName(keycode) << " (0x" << std::hex << std::uppercase << keycode << ')' << std::endl;
#endif
            OnReleased.Invoke();
            return true;
        case ButtonState::Disabled:
        case ButtonState::Idle:
            return false; // Ignore when disabled or idle (idle means it was just enabled, and we want to discard all left over held and released events)
        case ButtonState::Released:
        default:
            throw std::logic_error("[InputAction] Attempt to invoke OnReleased while in an invalid state (either Idle, Released, or some unknown state).");
            return false;
    }
}

void InputAction::SetStateToIdle()
{
    state = ButtonState::Idle;
}

void InputAction::SetStateToDisabled()
{
    state = ButtonState::Disabled;
}

// Protected Fields

// Protected Methods

// Private Fields

// Constructors

InputAction::InputAction(SDL_Keycode keycode) : keycode(keycode) {}

// Private Methods

} // namespace engine::Input
