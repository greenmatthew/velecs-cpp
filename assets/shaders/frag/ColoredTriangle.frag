/// @file    ColoredTriangle.frag
/// @author  Matthew Green
/// @date    2023-11-07 14:27:52
/// 
/// @section LICENSE
/// 
/// Copyright (c) 2023 Matthew Green - All rights reserved
/// Unauthorized copying of this file, via any medium is strictly prohibited
/// Proprietary and confidential

#version 450 // GLSL v4.5

layout(location = 0) in vec3 inColor; // Input color
layout(location = 0) out vec4 outFragColor; // Output color

void main()
{
    outFragColor = vec4(inColor, 1.0f);
}
