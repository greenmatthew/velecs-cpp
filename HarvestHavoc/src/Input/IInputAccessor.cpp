/// \file    IInputAccessor.cpp
/// \author  Matthew Green
/// \date    10/17/2023 17:09:22
/// 
/// \section LICENSE
/// 
/// Copyright (c) 2023 Matthew Green - All rights reserved
/// Unauthorized copying of this file, via any medium is strictly prohibited
/// Proprietary and confidential

#include "Input/IInputAccessor.h"
#include "Input/Input.h"

namespace HarvestHavoc::Input {

// Public Fields

// Constructors and Destructors

IInputAccessor::IInputAccessor() : input(Input::GetInstance()) {}

IInputAccessor::~IInputAccessor() = default;

// Public Methods

// Protected Fields

// Protected Methods

// Private Fields

// Private Methods

} // namespace HarvestHavoc::Input
