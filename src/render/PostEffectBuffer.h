#pragma once

#include "GLEW/glew.h"
#include "FrameBuffer.h"
#include "../mesh_data/Texture.h"
#include "../mesh_data/Mesh.h"
#include "RenderBuffer.h"

class PostEffectBuffer
{
public:
    PostEffectBuffer(const int width, const int height);
    ~PostEffectBuffer();

    void bindFrameBuffer();
    void unbindFrameBuffer();

    void bindScreen();

private:
    Mesh *screen_mesh;

    FrameBuffer frame_buffer;
    Texture screen_tex;
    RenderBuffer render_buffer;
};