#ifndef GLOBAL_H
#define GLOBAL_H

#include "utils.h"
#include "scene/Model.h"
#include "scene/Camera.h"
#include "render/ShaderProgram.h"
#include "render/Renderer.h"
#include "render/FrameBuffer.h"

#endif

/* declaration of global variables */

namespace global
{
    extern GlutTimer timer;
    extern ShaderProgram *program_first;
    extern ShaderProgram *program_second;
    extern ShaderProgram *program;
    extern FrameBuffer *postEffectBuffer;

    extern Model *Palace;

    extern Camera camViewport;
    extern Renderer *renderer;

    extern float renderWidth;
    extern float renderHeight;
}

