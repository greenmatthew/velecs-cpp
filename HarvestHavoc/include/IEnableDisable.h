// -------------------------------------------------------------------------------
// Filename:    IEnableDisable.h
// Created by:  mgreen
// Created on:  10/16/2023 21:32:30
// -------------------------------------------------------------------------------
// Copyright (c) 2023 Matthew Green - All rights reserved
// Unauthorized copying of this file, via any medium is strictly prohibited
// Proprietary and confidential
// -------------------------------------------------------------------------------

#pragma once

#include <functional>

namespace HarvestHavoc {

/// <summary>
/// Summary of class
/// </summary>
class IEnableDisable {
public:
    // Enums

    // Public Fields

    // Destructors
    virtual ~IEnableDisable() = 0;

    // Public Methods
    virtual void Enable();
    virtual void Disable();
    bool GetIsEnabled() const;

protected:
    // Protected Fields
    bool isEnabled = true;

    // Protected Methods

private:
    // Private Fields

    // Private Methods
};

} // namespace HarvestHavoc
