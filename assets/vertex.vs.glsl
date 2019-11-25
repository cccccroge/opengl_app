#version 420 core

layout(location = 0) in vec3 iv3vertex;
layout(location = 1) in vec3 iv3normal;
layout(location = 2) in vec2 iv2tex_coord;

uniform mat4 um4mvp;

out VertexData
{
    vec3 N; // eye space normal
    vec3 L; // eye space light vector
    vec3 H; // eye space halfway vector
    vec2 texcoord;
    vec3 normal;
} vertexData;

void main()
{
	gl_Position = um4mvp * vec4(iv3vertex, 1.0);
    vertexData.texcoord = iv2tex_coord;
    vertexData.normal = iv3normal;
}