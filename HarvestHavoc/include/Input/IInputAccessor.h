/// \file    IInputAccessor.h
/// \author  Matthew Green
/// \date    10/17/2023 17:07:08
/// 
/// \section LICENSE
/// 
/// Copyright (c) 2023 Matthew Green - All rights reserved
/// Unauthorized copying of this file, via any medium is strictly prohibited
/// Proprietary and confidential

#pragma once

namespace HarvestHavoc::Input {

class Input;

/// \class IInputAccessor
/// \brief Facilitates controlled access to input functionalities.
/// 
/// The IInputAccessor class serves as an interface to provide controlled access to input 
/// functionalities. By inheriting from this class, derived classes can gain access to 
/// certain input operations through the protected 'input' field.
class IInputAccessor {
public:
    // Enums

    // Public Fields

    // Constructors and Destructors

    /// \brief Default constructor.
    IInputAccessor();
    
    /// \brief Virtual destructor.
    virtual ~IInputAccessor() = 0;

    // Public Methods

protected:
    // Protected Fields

    Input& input; /// \brief Provides access to input functionalities.

    // Protected Methods

private:
    // Private Fields

    // Private Methods
};

} // namespace HarvestHavoc::Input
