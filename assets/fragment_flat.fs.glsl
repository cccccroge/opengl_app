#version 420 core

layout(location = 0) out vec4 fragColor;


in VertexData
{
    vec3 N; // eye space normal
    vec3 L; // eye space light vector
    vec3 H; // eye space halfway vector
    vec2 texcoord;
    vec3 normal;
} vertexData;

uniform sampler2D tex0;

void main()
{
    vec4 texColor = texture(tex0, vertexData.texcoord);
    if (texColor.a < 0.5)
        discard;
    else
        fragColor = texColor;
}