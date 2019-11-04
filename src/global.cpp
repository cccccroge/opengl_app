#include "global.h"

/* global variables definition (temporarily) */
GlutTimer global::timer = GlutTimer(16);
Camera global::cameraPersp = Camera();
Renderer global::renderer = Renderer();
float global::renderWidth = 0;
float global::renderHeight = 0;