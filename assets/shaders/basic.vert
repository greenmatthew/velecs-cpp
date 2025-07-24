#version 450

// Vertex inputs
layout(location = 0) in vec3 inPosition;
layout(location = 1) in vec4 inColor;

// Output to fragment shader
layout(location = 0) out vec4 fragColor;

vec4 unpackColor(uint packedColor) {
    return vec4(
        float((packedColor >> 24u) & 0xFFu) / 255.0,  // R
        float((packedColor >> 16u) & 0xFFu) / 255.0,  // G
        float((packedColor >> 8u)  & 0xFFu) / 255.0,  // B
        float( packedColor         & 0xFFu) / 255.0   // A
    );
}

void main()
{
    // Transform vertex by world matrix
    gl_Position = vec4(inPosition, 1.0);

    // Pass vertex color to fragment shader
    fragColor = inColor;
}
