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

layout( push_constant ) uniform constants
{
    vec4 color;
    mat4 renderMatrix;
} PushConstants;


layout(location = 0) out vec4 outFragColor; // Output color

void main()
{
    outFragColor = PushConstants.color;
}
