// -------------------------------------------------------------------------------
// Filename:    IEnableDisable.cpp
// Created by:  mgreen
// Created on:  10/16/2023 22:51:46
// -------------------------------------------------------------------------------
// Copyright (c) 2023 Matthew Green - All rights reserved
// Unauthorized copying of this file, via any medium is strictly prohibited
// Proprietary and confidential
// -------------------------------------------------------------------------------

#include "IEnableDisable.h"

namespace HarvestHavoc {

// Public Fields

// Constructors and Destructors
IEnableDisable::~IEnableDisable() = default;

// Public Methods
void IEnableDisable::Enable()
{
    isEnabled = true;
}

void IEnableDisable::Disable()
{
    isEnabled = false;
}

bool IEnableDisable::GetIsEnabled() const
{
    return isEnabled;
}

// Protected Fields

// Protected Methods

// Private Fields

// Private Methods

} // namespace HarvestHavoc::
