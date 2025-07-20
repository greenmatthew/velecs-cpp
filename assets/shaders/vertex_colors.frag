#version 450

// Input from vertex shader
layout(location = 0) in vec4 fragColor;

// Output color (need to specify location)
layout(location = 0) out vec4 outColor;

void main()
{
    outColor = fragColor;
}
