/// @file    Simple2DMesh.frag
/// @author  Matthew Green
/// @date    2023-11-26 13:48:01
/// 
/// @section LICENSE
/// 
/// Copyright (c) 2023 Matthew Green - All rights reserved
/// Unauthorized copying of this file, via any medium is strictly prohibited
/// Proprietary and confidential

#version 450 // GLSL v4.5

// Optional: Define some macros or constants here

//push constants block
layout( push_constant ) uniform constants
{
    vec4 color;
    mat4 renderMatrix;
} PushConstants;


layout(location = 0) out vec4 outFragColor; // Output color

// Optional: Define some uniform variables here

void main()
{
    outFragColor = PushConstants.color;
}
