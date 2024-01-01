/// @file    GLMUtility.cpp
/// @author  Matthew Green
/// @date    2023-12-28 18:49:39
/// 
/// @section LICENSE
/// 
/// Copyright (c) 2023 Matthew Green - All rights reserved
/// Unauthorized copying of this file, via any medium is strictly prohibited
/// Proprietary and confidential

#include "velecs/Math/GLMUtility.h"

namespace velecs {

// Public Fields

// Constructors and Destructors

// Public Methods

std::string GLMUtility::ToString(const glm::mat4& mat)
{
    std::ostringstream oss;
    oss << std::fixed << std::setprecision(6);  // Set fixed-point notation and precision
    for (int row = 0; row < 4; ++row)
    {
        oss << "[ ";
        for (int col = 0; col < 4; ++col)
        {
            oss << mat[col][row] << ' ';  // Access elements in column-major order
        }
        oss << "]\n";
    }
    return oss.str();  // Return the constructed string
}

// Protected Fields

// Protected Methods

// Private Fields

// Private Methods

} // namespace velecs
