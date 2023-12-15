/// @file    Simple2DMesh.vert
/// @author  Matthew Green
/// @date    2023-11-26 13:48:23
/// 
/// @section LICENSE
/// 
/// Copyright (c) 2023 Matthew Green - All rights reserved
/// Unauthorized copying of this file, via any medium is strictly prohibited
/// Proprietary and confidential

#version 450 // GLSL v4.5

layout (location = 0) in vec3 vPosition;

layout (location = 0) out vec4 outColor;

//push constants block
layout( push_constant ) uniform constants
{
    vec4 color;
    mat4 renderMatrix;
} PushConstants;

void main()
{
    gl_Position = PushConstants.renderMatrix * vec4(vPosition, 1.0f);
}