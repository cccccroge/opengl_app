#pragma once

#include "GLEW/glew.h"
#include "../init.h"

/* For now this class serve as task specific frame buffer (do post effect) */
class FrameBuffer
{
public:
    FrameBuffer();
    void bind();
    void unbind();
    void useScreenVertexTexture();

private:
    GLuint fbo;
    GLuint tbo;
    GLuint rbo;

    GLuint vao;
    GLuint vbo;
};