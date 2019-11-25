#version 420 core

layout(location = 0) out vec4 fragColor;

in ScreenData
{
    vec2 texCoord;
} screenData;

uniform sampler2D screenTex;

uniform float uf_comp_bar_xCoord;
uniform int ui_window_width;
uniform int ui_window_height;
uniform int ui_current_shader;

void main()
{
    if (ui_current_shader == 0 || ui_current_shader == 1) {
        fragColor = texture(screenTex, screenData.texCoord);
    }
    
}