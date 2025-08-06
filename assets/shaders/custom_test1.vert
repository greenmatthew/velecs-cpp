#version 450

layout(push_constant) uniform constants
{
    vec4 data1;
    vec4 data2;
    vec4 data3;
    vec4 data4;
} PushConstants;

layout (location = 0) out vec4 outColor;

void main() 
{
    const vec3 positions[3] = vec3[3](
        vec3( 1.0f,  1.0f,  0.0f),
        vec3(-1.0f,  1.0f,  0.0f),
        vec3( 0.0f, -1.0f,  0.0f)
    );

    const vec4 colors[3] = vec4[3](
        PushConstants.data1,
        PushConstants.data2,
        PushConstants.data3
    );

    gl_Position = vec4(positions[gl_VertexIndex], 1.0f);
    outColor = colors[gl_VertexIndex];
}
