#version 420 core

in ScreenData
{
    vec2 texCoord;

} screenData;

uniform sampler2D screenTex;

layout(location = 0) out vec4 fragColor;


void main()
{
    fragColor = texture(screenTex, screenData.texCoord);
}