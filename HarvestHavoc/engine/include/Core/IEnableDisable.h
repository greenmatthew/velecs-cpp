/// \file    IEnableDisable.h
/// \author  Matthew Green
/// \date    10/16/2023 21:32:30
/// 
/// \section LICENSE
/// 
/// Copyright (c) 2023 Matthew Green - All rights reserved
/// Unauthorized copying of this file, via any medium is strictly prohibited
/// Proprietary and confidential

#pragma once

#include "Input/IEnableDisablePassKey.h"

namespace HarvestHavocEngine {

class IEnableDisablePassKey;

/// <summary>
/// Interface for objects that can be enabled or disabled. Provides methods to 
/// request a change in state and handles those requests at a later time.
/// </summary>
class IEnableDisable {
public:
    // Public Fields

    // Destructors

    /// <summary>
    /// Virtual destructor to allow for derived class destructors to be called.
    /// </summary>
    virtual ~IEnableDisable() = 0;

    // Public Methods

    /// <summary>
    /// Request to enable the object. The actual enabling will happen later when HandleRequests is called.
    /// </summary>
    virtual void RequestEnable();

    /// <summary>
    /// Request to disable the object. The actual disabling will happen later when HandleRequests is called.
    /// </summary>
    virtual void RequestDisable();
    
    /// <summary>
    /// Check if the object is enabled.
    /// </summary>
    /// <returns>True if the object is enabled, false otherwise.</returns>
    bool GetIsEnabled() const;
    
    /// <summary>
    /// Processes any pending requests to enable or disable the object.
    /// </summary>
    void HandleRequests(Input::IEnableDisablePassKey passKey);

protected:
    // Protected Fields

    // Protected Methods

    /// <summary>
    /// Method to be overridden in derived classes. Will be called when the object is enabled.
    /// </summary>
    virtual void OnEnable() {}

    /// <summary>
    /// Method to be overridden in derived classes. Will be called when the object is disabled.
    /// </summary>
    virtual void OnDisable() {}

private:
    // Enums

    /// <summary>
    /// Enum to hold the requested state change.
    /// </summary>
    enum class RequestState
    {
        None,
        Enable,
        Disable,
    };

    // Private Fields
    
    /// <summary>
    /// Holds the current enabled/disabled state of the object.
    /// </summary>
    bool isEnabled = true;

    /// <summary>
    /// Holds the requested state change, if any.
    /// </summary>
    RequestState state = RequestState::None;

    // Private Methods

    /// <summary>
    /// Executes the enabling of the object, and calls OnEnable.
    /// </summary>
    void ExecuteEnable();

    /// <summary>
    /// Executes the disabling of the object, and calls OnDisable.
    /// </summary>
    void ExecuteDisable();
};

} // namespace HarvestHavocEngine
