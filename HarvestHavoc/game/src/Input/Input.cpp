/// \file    Input.cpp
/// \author  Matthew Green
/// \date    10/24/2023 20:56:44
/// 
/// \section LICENSE
/// 
/// Copyright (c) 2023 Matthew Green - All rights reserved
/// Unauthorized copying of this file, via any medium is strictly prohibited
/// Proprietary and confidential

#include "Input/Input.h"
#include "Input/PlayerInputActionMap.h"
#include "Input/MenuInputActionMap.h"

namespace HarvestHavoc::Input {

// Public Fields

std::shared_ptr<PlayerInputActionMap> Input::Player = Input::CreateMap<PlayerInputActionMap>();
std::shared_ptr<MenuInputActionMap> Input::Menu = Input::CreateMap<MenuInputActionMap>();

// Constructors and Destructors

// Public Methods

void Input::Init()
{
	Input::Player->Switch();
}

void Input::SwitchTo(std::shared_ptr<HarvestHavocEngine::Input::InputActionMap> inputActionMapPtr)
{
    Input::GetInstance().InternalSwitchTo(inputActionMapPtr);
}

// Protected Fields

// Protected Methods

// Private Fields

// Private Methods

} // namespace HarvestHavoc::Input
