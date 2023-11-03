#version 450 // GLSL v4.5
#extension GL_KHR_vulkan_glsl : enable // Allow Vulkan GLSL compatibility

// Optional: Define some macros or constants here

// Optional: Define some uniform variables here

layout(location = 0) in vec3 inPosition; // Input vertex position
layout(location = 1) in vec4 inColor; // Input vertex color

layout(location = 0) out vec4 vertColor; // Output vertex color to fragment shader

void main()
{
    gl_Position = vec4(inPosition, 1.0); // Set vertex position
    vertColor = inColor; // Pass color to fragment shader
}
