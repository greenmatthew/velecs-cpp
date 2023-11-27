/// @file    SimpleMesh.cpp
/// @author  Matthew Green
/// @date    2023-11-26 16:41:46
/// 
/// @section LICENSE
/// 
/// Copyright (c) 2023 Matthew Green - All rights reserved
/// Unauthorized copying of this file, via any medium is strictly prohibited
/// Proprietary and confidential

#include "velecs/ECS/Components/Rendering/SimpleMesh.h"

#include "velecs/Math/Vec3.h"

namespace velecs {

// Public Fields

const SimpleMesh SimpleMesh::EQUILATERAL_TRIANGLE
{
    std::vector<SimpleVertex>
    {
        // Equilateral Triangle (Counter-Clockwise)
        SimpleVertex{ Vec3{  0.0f, -0.5f,  0.0f } }, // Top
        SimpleVertex{ Vec3{ -0.5f,  0.5f,  0.0f } }, // Left
        SimpleVertex{ Vec3{  0.5f,  0.5f,  0.0f } }, // Right
    }
};

const SimpleMesh SimpleMesh::SQUARE
{
    std::vector<SimpleVertex>
    {
        // First Triangle (Counter-Clockwise)
        SimpleVertex{ Vec3{ -0.5f, -0.5f, 0.0f } }, // Top Left
        SimpleVertex{ Vec3{ -0.5f,  0.5f, 0.0f } }, // Bottom Left
        SimpleVertex{ Vec3{  0.5f,  0.5f, 0.0f } }, // Bottom Right

        // Second Triangle (Counter-Clockwise)
        SimpleVertex{ Vec3{ -0.5f, -0.5f, 0.0f } }, // Top Left
        SimpleVertex{ Vec3{  0.5f,  0.5f, 0.0f } }, // Bottom Right
        SimpleVertex{ Vec3{  0.5f, -0.5f, 0.0f } }, // Top Right
    }
};

// Constructors and Destructors

// Public Methods

// Protected Fields

// Protected Methods

// Private Fields

// Private Methods

} // namespace velecs
