/// \file    IEnableDisable.cpp
/// \author  mgreen
/// \date    10/16/2023 22:51:46
/// 
/// \section LICENSE
/// 
/// Copyright (c) 2023 Matthew Green - All rights reserved
/// Unauthorized copying of this file, via any medium is strictly prohibited
/// Proprietary and confidential

#include "Core/IEnableDisable.h"

namespace engine {

// Public Fields

// Constructors and Destructors

IEnableDisable::~IEnableDisable() = default;

// Public Methods

void IEnableDisable::RequestEnable()
{
    state = RequestState::Enable;
}

void IEnableDisable::RequestDisable()
{
    state = RequestState::Disable;
}

bool IEnableDisable::GetIsEnabled() const
{
    return isEnabled;
}

// Protected Fields

// Protected Methods

// Private Fields

// Private Methods

void IEnableDisable::ExecuteEnable()
{
    state = RequestState::None;
    isEnabled = true;
    OnEnable();
}

void IEnableDisable::ExecuteDisable()
{
    state = RequestState::None;
    isEnabled = false;
    OnDisable();
}

void IEnableDisable::HandleRequests(IEnableDisablePassKey passKey)
{
    switch (state)
    {
        case RequestState::Enable:
            ExecuteEnable();
            break;
        case RequestState::Disable:
            ExecuteDisable();
            break;
        case RequestState::None:
        default:
            break;
    }
}

} // namespace engine
