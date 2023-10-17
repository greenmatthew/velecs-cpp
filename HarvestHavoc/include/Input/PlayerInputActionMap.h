// -------------------------------------------------------------------------------
// Filename:    PlayerInputActionMap.h
// Created by:  mgreen
// Created on:  10/16/2023 18:49:35
// -------------------------------------------------------------------------------
// Copyright (c) 2023 Matthew Green - All rights reserved
// Unauthorized copying of this file, via any medium is strictly prohibited
// Proprietary and confidential
// -------------------------------------------------------------------------------

#pragma once

#include "Input/InputActionMap.h"

namespace HarvestHavoc::Input {

/// <summary>
/// Summary of class
/// </summary>
class PlayerInputActionMap : public InputActionMap {
public:
    // Enums

    // Public Fields
    std::shared_ptr<InputAction> LeftStrafe;
    std::shared_ptr<InputAction> RightStrafe;

    // Constructors and Destructors
    PlayerInputActionMap() = default;
    ~PlayerInputActionMap() = default;

    // Public Methods
    void Init() override;
    
protected:
    // Protected Fields

    // Protected Methods

private:
    // Private Fields

    // Private Methods
};

} // namespace HarvestHavoc::Input
