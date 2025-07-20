#version 450

// Vertex attributes from vertex buffer
layout(location = 0) in vec3 inPosition;
layout(location = 1) in vec4 inColor;

// // Push constants (optional - for transformations)
// layout(push_constant) uniform PushConstants {
//     mat4 transform; // Or just mat4 mvp;
// } pc;

// Output to fragment shader
layout(location = 0) out vec4 fragColor;

void main()
{
    // Transform the vertex position
    // gl_Position = pc.transform * vec4(inPosition, 1.0);
    gl_Position = vec4(inPosition, 1.0);
    
    // Pass vertex color to fragment shader
    fragColor = inColor;
}