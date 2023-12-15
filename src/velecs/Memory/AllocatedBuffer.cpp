/// @file    AllocatedBuffer.cpp
/// @author  Matthew Green
/// @date    2023-11-26 23:04:55
/// 
/// @section LICENSE
/// 
/// Copyright (c) 2023 Matthew Green - All rights reserved
/// Unauthorized copying of this file, via any medium is strictly prohibited
/// Proprietary and confidential

#include "velecs/Memory/AllocatedBuffer.h"

namespace velecs {

// Public Fields

// Constructors and Destructors

bool AllocatedBuffer::IsInitialized() const
{
    return _buffer != nullptr && _allocation != nullptr;
}

// Public Methods

// Protected Fields

// Protected Methods

// Private Fields

// Private Methods

} // namespace velecs
