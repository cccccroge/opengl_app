#include "callback.h"
#include "utils.h"
#include "init.h"
#include "freeGLUT/freeglut.h"

#include "GLM/glm_996/vec3.hpp"
#include "GLM/glm_996/ext/matrix_transform.hpp"
#include "GLM/glm_996/gtc/type_ptr.hpp"

#include <iostream>
#include "global.h"
#include "scene/Mesh.h"


void onMenuTriggered(int id)
{
	switch(id)
	{
	case MENU_TIMER_START:
		global::timer.Start();
		break;
	case MENU_TIMER_STOP:
		global::timer.Pause();
		break;
	case MENU_EXIT:
		exitProgram();
		break;
	case MENU_IDLE:
		global::timer.animated = false;
		break;
	case MENU_SUPERMAN:
		global::timer.animated = true;
		break;
	default:
		break;
	}
}


// GLUT callback. Called to draw the scene.
void onDisplayRefresh(void)
{
	global::renderer->RenderAll();
}


// Setting up viewing matrix
void onWindowReshaped(int width, int height)
{
	global::renderWidth = width;
	global::renderHeight = height;
	glViewport(0, 0, global::renderWidth, global::renderHeight);
}


void onKeyboardPressed(unsigned char key, int x, int y)
{
	if (!GlutTimer::enabled)
		return;

	switch(key) {
		case 'd':
		global::Torso->translate(0.5f, 0.0f, 0.0f);
		break;

		case 'a':
		global::Torso->translate(-0.5f, 0.0f, 0.0f);
		break;

		case 'w':
		global::Torso->translate(0.0f, 0.0f, 0.5f);
		break;

		case 's':
		global::Torso->translate(0.0f, 0.0f, -0.5f);
		break;

		case 'x':
		global::Torso->rotate(5.0f, std::vector<float>({ 1.0f, 0.0f, 0.0f }));
		break;

		case 'y':
		global::Torso->rotate(5.0f, std::vector<float>({ 0.0f, 1.0f, 0.0f }));
		break;

		case 'z':
		global::Torso->rotate(5.0f, std::vector<float>({ 0.0f, 0.0f, 1.0f }));
		break;

		case 'f':
		glutFullScreenToggle();
		break;
	}
}


void onSpecialkeysPressed(int key, int x, int y)
{
	if (!GlutTimer::enabled)
		return;

	switch(key)
	{
	case GLUT_KEY_F1:
		printf("F1 is pressed at (%d, %d)\n", x, y);
		break;

	default:
		printf("Other special key is pressed at (%d, %d)\n", x, y);
		break;
	}
}


void onMousePressed(int button, int state, int x, int y)
{
	if (!GlutTimer::enabled)
		return;
		
	if (button == GLUT_LEFT_BUTTON)
	{
		if (state == GLUT_DOWN)
		{
			printf("Mouse %d is pressed at (%d, %d)\n", button, x, y);
		}
		else if (state == GLUT_UP)
		{
			printf("Mouse %d is released at (%d, %d)\n", button, x, y);
		}
	}
}


void onWindowClosed(void)
{
	exitProgram();
}


void onMouseWheelSpinned(int wheel, int direction, int x, int y)
{
	if (wheel != 0) {
		std::cout << "spinning non-default wheel!" << std::endl;
		return;
	}

	// move camera toward its face direction
	Camera* cam = global::renderer->getCamera();
	glm::vec3 dir = (float)direction * cam->getDirection();
	glm::vec3 mov = SCALE_SENSITIVITY * dir;
	cam->translate(mov[0], mov[1], mov[2]);
	cam->setLookPos(cam->getLookPos() + mov);	// update cam's lookPos
}