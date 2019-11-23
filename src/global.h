#ifndef GLOBAL_H
#define GLOBAL_H

#include "utils.h"
#include "scene/Model.h"
#include "scene/Camera.h"
#include "render/ShaderProgram.h"
#include "render/Renderer.h"

#endif

/* declaration of global variables */

namespace global
{
    extern GlutTimer timer;
    extern ShaderProgram *program;

    extern Model *Torso;
    extern Model *Head;
    extern Model *Arm_R1;
    extern Model *Arm_R2;
    extern Model *Arm_L1;
    extern Model *Arm_L2;
    extern Model *Leg_R1;
    extern Model *Leg_R2;
    extern Model *Leg_L1;
    extern Model *Leg_L2;

    extern Camera camViewport;
    extern Renderer *renderer;

    extern float renderWidth;
    extern float renderHeight;
}

