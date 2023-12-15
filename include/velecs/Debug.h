/// @file    Debug.h
/// @author  Matthew Green
/// @date    10/17/2023 17:35:35
/// 
/// @section LICENSE
/// 
/// Copyright (c) 2023 Matthew Green - All rights reserved
/// Unauthorized copying of this file, via any medium is strictly prohibited
/// Proprietary and confidential

#pragma once

// Define DEBUG_MODE if either _DEBUG (Visual Studio) or NDEBUG (not in Release mode, typically CMake) is defined.
#if defined(_DEBUG) || !defined(NDEBUG)
    #define DEBUG_MODE // Comment out if you want to turn off debug code, without modifying the VS project.
#endif

#ifdef DEBUG_MODE

#endif
