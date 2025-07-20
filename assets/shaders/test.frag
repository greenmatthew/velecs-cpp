#version 450

// Same push constant as vertex shader
layout(push_constant) uniform PushConstantData {
    mat4 model;
    vec4 color;
} pc;

// Same uniform buffer as vertex shader
layout(set = 0, binding = 0) uniform CameraUBO {
    mat4 view;
    mat4 proj;
    vec3 cameraPos;
} camera;

// Fragment-only texture
layout(set = 0, binding = 1) uniform sampler2D diffuseTexture;

// Inputs from vertex shader
layout(location = 0) in vec3 fragWorldPos;
layout(location = 1) in vec3 fragNormal;
layout(location = 2) in vec2 fragTexCoord;
layout(location = 3) in vec4 fragColor;

// Output
layout(location = 0) out vec4 outColor;

void main() {
    // Sample texture
    vec4 texColor = texture(diffuseTexture, fragTexCoord);
    
    // Simple lighting calculation
    vec3 lightDir = normalize(camera.cameraPos - fragWorldPos);
    vec3 normal = normalize(fragNormal);
    float lightIntensity = max(dot(normal, lightDir), 0.2); // Ambient + diffuse
    
    // Combine everything
    outColor = texColor * pc.color * lightIntensity;
}
