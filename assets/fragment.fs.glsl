#version 420 core

layout(location = 0) out vec4 fragColor;


in VertexData
{
    vec3 N; // eye space normal
    vec3 L; // eye space light vector
    vec3 H; // eye space halfway vector
    vec2 texcoord;
} vertexData;

uniform sampler2D tex;

void main()
{
    vec3 texColor = texture(tex,vertexData.texcoord).rgb;
    fragColor = vec4(texColor, 1.0);
    //fragColor = vec4(0.5, 0.2, 0.75, 1.0);
}