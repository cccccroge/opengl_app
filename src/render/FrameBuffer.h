#pragma once

#include "GLEW/glew.h"
#include "../init.h"
#include "../mesh_data/Texture.h"
#include "RenderBuffer.h"


class FrameBuffer
{
public:
    FrameBuffer();
    ~FrameBuffer();

    void attachTexture(Texture &tex);
    void attachRenderBuffer(RenderBuffer &render_buffer);
    bool validate();

    void bind();
    void unbind();

private:
    GLuint fbo;
};