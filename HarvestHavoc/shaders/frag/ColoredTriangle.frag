#version 450 // GLSL v4.5

layout(location = 0) in vec3 fragColor; // Input color
layout(location = 0) out vec4 outFragColor; // Output color

void main()
{
    outFragColor = vec4(fragColor, 1.0f);
}
