// -------------------------------------------------------------------------------
// Filename:    IInputAccessor.h
// Created by:  mgreen
// Created on:  10/17/2023 17:07:08
// -------------------------------------------------------------------------------
// Copyright (c) 2023 Matthew Green - All rights reserved
// Unauthorized copying of this file, via any medium is strictly prohibited
// Proprietary and confidential
// -------------------------------------------------------------------------------

#pragma once

namespace HarvestHavoc::Input {

class Input;

/// <summary>
/// Summary of class
/// </summary>
class IInputAccessor {
public:
    // Enums

    // Public Fields

    // Constructors and Destructors
    IInputAccessor();
    virtual ~IInputAccessor() = default;

    // Public Methods

protected:
    // Protected Fields
    Input& input;

    // Protected Methods

private:
    // Private Fields

    // Private Methods
};

} // namespace HarvestHavoc::Input
