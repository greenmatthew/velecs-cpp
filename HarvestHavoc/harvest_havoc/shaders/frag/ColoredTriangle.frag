#version 450 // GLSL v4.5

layout(location = 0) in vec3 inColor; // Input color
layout(location = 0) out vec4 outFragColor; // Output color

void main()
{
    outFragColor = vec4(inColor, 1.0f);
}
