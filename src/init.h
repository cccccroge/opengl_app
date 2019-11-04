#pragma once

#include "freeGLUT/freeglut.h"
#include "GLM/glm_996/vec3.hpp"

#define CONTEXT_VER_MAJOR 4
#define CONTEXT_VER_MINOR 2

#define MAINWINDOW_WIDTH 1024
#define MAINWINDOW_HEIGHT 576

#define MENU_TRIGGER_BUTTON GLUT_RIGHT_BUTTON
#define MENU_TIMER_START 1
#define MENU_TIMER_STOP 2
#define MENU_EXIT 3
#define MENU_IDLE 4
#define MENU_SUPERMAN 5

#define UP_VECTOR glm::vec3(0.0f, 1.0f, 0.0f)   // Y is up, consistent with OpenGL



/* --------------------------------------------------------------------
 * initGlutContext
 * Initialize freeGLUT and create a mainwindow as current context.
 * --------------------------------------------------------------------
 * argc and argv: main function arguments will be passed to here,
 * 
 * The window size is specified by MAINWINDOW_WIDTH and 
 * MAINWINDOW_HEIGHT. It will be placed at the center of client area by
 * default.
 * 
 * */
int initGlutContext(int argc, char *argv[]);


/* --------------------------------------------------------------------
 * initGlew
 * Initialize GLEW to obtain modern opengl extensions.
 * --------------------------------------------------------------------
 * 
 * Note that this initializtion function should be called right after
 * the very first gl context has been created. (eg. initGlutContext())
 * 
 * */
void initGlew(void);


/* --------------------------------------------------------------------
 * createMenu
 * Create GLUT pop-up menu when pressing MENU_TRIGGER_BUTTON.
 * --------------------------------------------------------------------
 * 
 * The implementation at this stage simply hard codes all the menu
 * entries, will be modified in future. (maybe)
 * 
 * */
void createMenu(void);


/* --------------------------------------------------------------------
 * registerCallbacks
 * Register some GLUT callback functions. All callback implementations
 * are defined in callback.cpp.
 * --------------------------------------------------------------------
 * 
 * Not all callback functions are included in this function. Sometimes
 * we need to register callback not only once to achieve some
 * functionalities. (eg. global timer)
 * 
 * */
void registerCallbacks(void);