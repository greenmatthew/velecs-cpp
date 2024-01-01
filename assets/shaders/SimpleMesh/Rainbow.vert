#version 450 // GLSL v4.5

#define PI 3.1415926535897932384626433832795

// layout(set = 0, binding = 0) uniform TimeUniform {
//     int time;
// } timeUniform;

layout (location = 0) in vec3 vPosition;

layout (location = 0) out vec4 outColor;

layout( push_constant ) uniform constants
{
    vec4 color;
    mat4 renderMatrix;
} PushConstants;

void main()
{
    const int t = 0;

    // Red Channel
    float xR = cos(t);

    // Green Channel
    float xG = cos(t + 2.0 * PI / 3.0);

    // Blue Channel
    float xB = cos(t + 4.0 * PI / 3.0);

    //const array of colors for the triangle
    const vec4 colors[3] = vec4[3]
    (
        vec4(clamp(xR, 0.0f, 1.0f), clamp(xG, 0.0f, 1.0f), clamp(xB, 0.0f, 1.0f), 1.0f),
        vec4(clamp(xB, 0.0f, 1.0f), clamp(xR, 0.0f, 1.0f), clamp(xG, 0.0f, 1.0f), 1.0f),
        vec4(clamp(xG, 0.0f, 1.0f), clamp(xB, 0.0f, 1.0f), clamp(xR, 0.0f, 1.0f), 1.0f)
    );

    vec4 pos = PushConstants.renderMatrix * vec4(vPosition, 1.0f);
    vec4 ndcPos = pos / pos.w;

    gl_Position = ndcPos;
    outColor = colors[gl_VertexIndex % 3];
}
