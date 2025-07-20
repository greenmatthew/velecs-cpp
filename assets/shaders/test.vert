#version 450

// Shared push constant
layout(push_constant) uniform PushConstantData {
    mat4 model;
    vec4 color;
} pc;

// Shared uniform buffer
layout(set = 0, binding = 0) uniform CameraUBO {
    mat4 view;
    mat4 proj;
    vec3 cameraPos;
} camera;

// Vertex inputs
layout(location = 0) in vec3 inPosition;
layout(location = 1) in vec3 inNormal;
layout(location = 2) in vec2 inTexCoord;

// Outputs to fragment shader
layout(location = 0) out vec3 fragWorldPos;
layout(location = 1) out vec3 fragNormal;
layout(location = 2) out vec2 fragTexCoord;
layout(location = 3) out vec4 fragColor;

void main() {
    // Transform vertex to world space
    vec4 worldPos = pc.model * vec4(inPosition, 1.0);
    fragWorldPos = worldPos.xyz;
    
    // Transform normal to world space (assuming uniform scaling)
    fragNormal = mat3(pc.model) * inNormal;
    
    // Pass through texture coordinates
    fragTexCoord = inTexCoord;
    
    // Pass through color from push constant
    fragColor = pc.color;
    
    // Final vertex position
    gl_Position = camera.proj * camera.view * worldPos;
}
