#version 450

// Uniform buffer
layout(set = 0, binding = 0) uniform ObjectUniforms {
    mat4 worldMatrix;
    vec4 color;  // Note: Color32 becomes vec4 in shader
} object;

// Vertex inputs
layout(location = 0) in vec3 inPosition;
layout(location = 1) in vec4 inColor;

// Output to fragment shader
layout(location = 0) out vec4 fragColor;

void main()
{
    // Transform the vertex position
    gl_Position = vec4(inPosition, 1.0);

    // Transform vertex by world matrix
    // gl_Position = object.worldMatrix * vec4(inPosition, 1.0);
    
    // Pass vertex color to fragment shader
    fragColor = object.color;
}