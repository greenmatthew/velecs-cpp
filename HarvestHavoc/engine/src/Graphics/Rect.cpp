/// \file    Rect.cpp
/// \author  Matthew Green
/// \date    11/01/2023 19:26:53
/// 
/// \section LICENSE
/// 
/// Copyright (c) 2023 Matthew Green - All rights reserved
/// Unauthorized copying of this file, via any medium is strictly prohibited
/// Proprietary and confidential

#include "Graphics/Rect.h"

namespace engine {

// Public Fields

// Constructors and Destructors

/// \brief Constructor.
Rect::Rect(const Vec2 min, const Vec2 max)
	: min(min), max(max) {}

/// \brief Constructor.
Rect::Rect(const float left, const float bottom, const float right, const float top)
	: min(Vec2{ left, bottom }), max(Vec2{ right, top }) {}

// Public Methods

// Protected Fields

// Protected Methods

// Private Fields

// Private Methods

} // namespace engine
