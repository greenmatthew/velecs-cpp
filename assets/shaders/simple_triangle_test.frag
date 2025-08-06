#version 450

// Vertex shader input
layout (location = 0) in vec3 inColor;

// Output write
layout (location = 0) out vec4 outFragColor;

void main() 
{
    outFragColor = vec4(inColor,1.0f);
}
