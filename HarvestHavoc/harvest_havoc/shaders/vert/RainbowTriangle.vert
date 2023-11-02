#version 450 // GLSL v4.5

#define PI 3.1415926535897932384626433832795

// layout(set = 0, binding = 0) uniform TimeUniform {
//     int time;
// } timeUniform;

layout(location = 0) out vec3 outColor;

void main()
{
    //const array of positions for the triangle
    const vec3 positions[3] = vec3[3]
    (
        vec3( 1.0f,  1.0f,  0.0f),
        vec3(-1.0f,  1.0f,  0.0f),
        vec3( 0.0f, -1.0f,  0.0f)
    );

    const int t = 0;

    // Red Channel
    float xR = cos(t);

    // Green Channel
    float xG = cos(t + 2.0 * PI / 3.0);

    // Blue Channel
    float xB = cos(t + 4.0 * PI / 3.0);

    //const array of colors for the triangle
    const vec3 colors[3] = vec3[3]
    (
        vec3(clamp(xR, 0.0f, 1.0f), clamp(xG, 0.0f, 1.0f), clamp(xB, 0.0f, 1.0f)),
        vec3(clamp(xB, 0.0f, 1.0f), clamp(xR, 0.0f, 1.0f), clamp(xG, 0.0f, 1.0f)),
        vec3(clamp(xG, 0.0f, 1.0f), clamp(xB, 0.0f, 1.0f), clamp(xR, 0.0f, 1.0f))
    );

    //output the position of each vertex
    gl_Position = vec4(positions[gl_VertexIndex], 1.0f);
    outColor = colors[gl_VertexIndex];
}
