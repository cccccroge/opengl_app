#include "callback.h"
#include "utils.h"
#include "init.h"
#include "freeGLUT/freeglut.h"

#include "GLM/glm_996/vec3.hpp"
#include "GLM/glm_996/ext/matrix_transform.hpp"
#include "GLM/glm_996/gtc/type_ptr.hpp"

#include <iostream>
#include <map>
#include "global.h"
#include "scene/Mesh.h"


// keyboard/mouse status record
std::map<std::string, bool> KEYS_PRESSED;
struct _MOUSE_POS
{
	int x;
	int y;

} MOUSE_POS;

// flag helper
bool shifted = false;	// whether mouse movement is shifted by program


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


void onKeyboardReleased(unsigned char key, int x, int y)
{
	switch(key)
	{
		default:
			std::cout << "some keys pressed" << std::endl;
			break;
	}
}


void onSpecialkeysPressed(int key, int x, int y)
{
	switch(key)
	{
		case GLUT_KEY_SHIFT_L:
		case GLUT_KEY_SHIFT_R:
			KEYS_PRESSED["shift"] = true;
			break;

		default:
			std::cout << "special keys pressed" << std::endl;
			break;
	}
}


void onSpecialkeysReleased(int key, int x, int y)
{
	switch(key)
	{
		case GLUT_KEY_SHIFT_L:
		case GLUT_KEY_SHIFT_R:
			KEYS_PRESSED["shift"] = false;
			break;

		default:
			std::cout << "special keys released" << std::endl;
			break;
	}
}


void onMousePressed(int button, int state, int x, int y)
{
	if (state == GLUT_DOWN) {
		switch (button) {
			case GLUT_MIDDLE_BUTTON:
				KEYS_PRESSED["mouse_mid"] = true;
				// update position
				MOUSE_POS.x = x;
				MOUSE_POS.y = y;
				break;
			
			default:
				break;
		}
	}

	else if (state == GLUT_UP) {
		switch (button) {
			case GLUT_MIDDLE_BUTTON:
				KEYS_PRESSED["mouse_mid"] = false;
				break;
			
			default:
				break;
		}
	}	
}


void onMouseMoved(int x, int y)
{
	if (KEYS_PRESSED["shift"] && KEYS_PRESSED["mouse_mid"]) {
/* 		if (shifted) {
			// ignore and flip
			shifted = false;
			return;
		} */

		// calculate movement
		int dx = x - MOUSE_POS.x;
		int dy = y - MOUSE_POS.y;

		// get pan direction
		glm::vec3 right = glm::normalize(
			glm::cross(global::camViewport.getDirection(), UP_VECTOR));
		glm::vec3 down = glm::normalize(
			glm::cross(global::camViewport.getDirection(), right));

		// move
		glm::vec3 movement = -PAN_SENSITIVITY * ((float)dx * right + (float)dy * down);
		global::camViewport.translate(movement);
		global::camViewport.setLookPos(global::camViewport.getLookPos() + movement);

		// update position
		MOUSE_POS.x = x;
		MOUSE_POS.y = y;
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

	global::camViewport.zoom(direction);
}