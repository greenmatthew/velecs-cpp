/// \file    Debug.h
/// \author  Matthew Green
/// \date    10/17/2023 17:35:35
/// 
/// \section LICENSE
/// 
/// Copyright (c) 2023 Matthew Green - All rights reserved
/// Unauthorized copying of this file, via any medium is strictly prohibited
/// Proprietary and confidential

#pragma once

/// \def _DEBUG
/// Check if _DEBUG macro is defined to enable debug mode. _DEBUG is VS' debug flag definition.
#ifdef _DEBUG

    #define DEBUG_MODE // Comment out if you want to turn off debug code, without modifying the VS project.
    
#endif

/// \def DEBUG_MODE
/// Define DEBUG_MODE if _DEBUG is defined.
#ifdef DEBUG_MODE

    /// \def DEBUG_INPUTACTION
    /// Enable additional debugging for input actions.
    // #define DEBUG_INPUTACTION
    
    #ifdef DEBUG_INPUTACTION
        /// \def DEBUG_INPUTACTION_HELD
        /// Uncomment to enable debugging for held input actions.
        // #define DEBUG_INPUTACTION_HELD
    #endif

#endif