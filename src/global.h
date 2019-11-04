#ifndef GLOBAL_H
#define GLOBAL_H

#include "utils.h"
#include "scene/Mesh.h"
#include "scene/Camera.h"
#include "render/ShaderProgram.h"
#include "render/Renderer.h"

#endif

/* declaration of global variables */

namespace global
{
    extern GlutTimer timer;
    extern ShaderProgram *program;

    extern Mesh *Torso;
    extern Mesh *Head;
    extern Mesh *Arm_R1;
    extern Mesh *Arm_R2;
    extern Mesh *Arm_L1;
    extern Mesh *Arm_L2;
    extern Mesh *Leg_R1;
    extern Mesh *Leg_R2;
    extern Mesh *Leg_L1;
    extern Mesh *Leg_L2;

    extern Camera cameraPersp;
    extern Renderer *renderer;

    extern float renderWidth;
    extern float renderHeight;
}

