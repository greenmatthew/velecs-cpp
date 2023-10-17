// -------------------------------------------------------------------------------
// Filename:    MenuInputActionMap.h
// Created by:  mgreen
// Created on:  10/16/2023 18:49:47
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
class MenuInputActionMap : public InputActionMap {
public:
    // Enums

    // Public Fields

    // Constructors and Destructors
    MenuInputActionMap() = default;
    ~MenuInputActionMap() = default;

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
