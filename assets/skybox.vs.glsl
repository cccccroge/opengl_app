#version 420 core

layout(location = 0) in vec3 pos;
uniform mat4 um4mvp;

out vec3 texCoord;  // note this should be vec3 as direction vector


void main()
{
    gl_Position = um4mvp * vec4(pos, 1.0);
    texCoord = pos;
}