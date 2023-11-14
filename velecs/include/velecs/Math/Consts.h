/// @file    Consts.h
/// @author  Matthew Green
/// @date    10/15/2023 12:36:20
/// 
/// @section LICENSE
/// 
/// Copyright (c) 2023 Matthew Green - All rights reserved
/// Unauthorized copying of this file, via any medium is strictly prohibited
/// Proprietary and confidential

#pragma once

#include <limits>

namespace velecs {

    constexpr float PI = 3.14159265358979323846f; /// @brief The mathematical constant Pi (π).
    constexpr float DEG_TO_RAD = PI / 180.0f; /// @brief Conversion factor to convert degrees to radians.
    constexpr float RAD_TO_DEG = 180.0f / PI; /// @brief Conversion factor to convert radians to degrees.
    constexpr float FLOAT_POS_INFINITY = std::numeric_limits<float>::infinity(); /// @brief Representation of positive infinity in floating-point.
    constexpr float FLOAT_NEG_INFINITY = -FLOAT_POS_INFINITY; /// @brief Representation of negative infinity in floating-point.

} // namespace velecs
