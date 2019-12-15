#version 420 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 normal;
layout(location = 2) in vec2 texCoord;

uniform mat4 mvpMatrix;
uniform mat4 mMatrix;

out VertexData
{
    vec3 position;
    vec3 normal;
    vec2 texCoord;

} vertexData;

out BlinnPhongData
{
    vec3 fragPos;
    vec3 normal;    // in world space

} blinnPhongData;


void main()
{
    // pass to fragment shader
    vertexData.position = position;
    vertexData.normal = normal;
    vertexData.texCoord = texCoord;

    blinnPhongData.fragPos = vec3(mMatrix * vec4(position, 1.0));
    blinnPhongData.normal = mat3(transpose(inverse(mMatrix))) * normal;

    // calculate vertex position
	gl_Position = mvpMatrix * vec4(position, 1.0);
}