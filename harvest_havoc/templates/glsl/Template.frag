#version 450 // GLSL v4.5
#extension GL_KHR_vulkan_glsl : enable // Allow Vulkan GLSL compatibility

// Optional: Define some macros or constants here

layout(location = 0) in vec4 fragColor; // Input color
layout(location = 0) out vec4 outFragColor; // Output color

// Optional: Define some uniform variables here

void main()
{
    outFragColor = fragColor;
}
