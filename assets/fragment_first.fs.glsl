#version 420 core

layout(location = 0) out vec4 fragColor;

in VertexData
{
    vec2 texcoord;
    vec3 normal;
} vertexData;

in vec4 gl_FragCoord;

uniform sampler2D tex0;
uniform float uf_comp_bar_xCoord;
uniform int ui_window_width;
uniform int ui_window_height;
uniform int ui_current_shader;


void flatShader()
{
    vec4 texColor = texture(tex0, vertexData.texcoord);
    if (texColor.a < 0.5) {
        discard;
    }
    else {
        fragColor = texColor;
    }
}

void normalAsColor()
{
    fragColor = vec4(vertexData.normal, 1.0);
}


void main()
{
    if ((gl_FragCoord.x / ui_window_width) > uf_comp_bar_xCoord) {

        // normal
        if (ui_current_shader == 0) {
            flatShader();
        }

        // normal as color
        else if (ui_current_shader == 1) {
            normalAsColor();
        }  
        
    }

    else {
        flatShader();
    }
}