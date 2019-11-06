#include "callback.h"
#include "../utils.h"
#include "../init.h"
#include "freeGLUT/freeglut.h"

#include "GLM/glm_996/vec3.hpp"
#include "GLM/glm_996/ext/matrix_transform.hpp"
#include "GLM/glm_996/gtc/type_ptr.hpp"

#include <iostream>
#include <map>
#include <set>
#include "../global.h"
#include "../scene/Mesh.h"
#include "keymap.h"


// keyboard/mouse status record
std::map<std::string, bool> KEYS_PRESSED;
std::set<std::string> pressedKeySet;

struct _MOUSE_POS
{
	int x;
	int y;

} MOUSE_POS;

// flag helper
bool shifted = false;	// whether mouse movement is shifted by program
TOOL_MODE toolMode = TOOL_MODE::NONE;


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


void onDisplayRefresh(void)
{
	global::renderer->RenderAll();
}


void onWindowReshaped(int width, int height)
{
	global::renderWidth = width;
	global::renderHeight = height;
	glViewport(0, 0, global::renderWidth, global::renderHeight);
}


void onKeyboardPressed(unsigned char key, int x, int y)
{
	std::string keyStr(1, key);
	if (!KEYS_PRESSED[keyStr]) {
		pressedKeySet.insert(keyStr);
		checkTool(keyStr);
	}
	
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

		default:
			std::cout << "some keys pressed" << std::endl;
			break;
	}
}


void onKeyboardReleased(unsigned char key, int x, int y)
{
	std::string keyStr(1, key);
	pressedKeySet.erase(keyStr);
	
	switch(key)
	{
		case 'd':
			break;

		case 'a':
			break;

		case 'w':
			break;

		case 's':
			break;

		case 'x':
			break;

		case 'y':
			break;

		case 'z':
			break;

		case 'f':
			glutFullScreenToggle();
			break;

		default:
			std::cout << "some keys released" << std::endl;
			break;
	}
}


void onSpecialkeysPressed(int key, int x, int y)
{
	std::string keyStr = btn2str(key);
	if (!KEYS_PRESSED[keyStr]) {
		pressedKeySet.insert(keyStr);
		checkTool(keyStr);
	}

	switch(key)
	{
		default:
			std::cout << "special keys pressed" << std::endl;
			break;
	}
}


void onSpecialkeysReleased(int key, int x, int y)
{
	std::string keyStr = btn2str(key);
	pressedKeySet.erase(keyStr);

	switch(key)
	{
		default:
			std::cout << "special keys released" << std::endl;
			break;
	}
}


void onMousePressed(int button, int state, int x, int y)
{
	if (state == GLUT_DOWN) {

		std::string keyStr = btn2str(button);
		if (!KEYS_PRESSED[keyStr]) {
			pressedKeySet.insert(keyStr);
			checkTool(keyStr);
		}

		if (toolMode == TOOL_MODE::ORBIT || 
			toolMode == TOOL_MODE::PAN) {
			MOUSE_POS.x = x;
			MOUSE_POS.y = y;
		}
	}

	else if (state == GLUT_UP) {

		std::string keyStr = btn2str(button);
		pressedKeySet.erase(keyStr);

		checkTool("");
	}	
}


void onMouseMoved(int x, int y)
{
	if (toolMode == TOOL_MODE::ORBIT || 
		toolMode == TOOL_MODE::PAN) {

		onMouseMovedDelta(x - MOUSE_POS.x, y - MOUSE_POS.y);
		MOUSE_POS.x = x;
		MOUSE_POS.y = y;
	}
}


void onMouseMovedDelta(int dx, int dy)
{
	if (toolMode == TOOL_MODE::PAN) {
		global::camViewport.pan(dx, dy);
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


bool checkTool(std::string last)
{
	// deactivate
	if (last == "") {
		TOOL_MODE toolMode = TOOL_MODE::NONE;
		return false;
	}


	// activate if find
	std::set<std::string> current = pressedKeySet;
	current.erase(last);

	if (current.size() != 0) {	// has pressed button set
		for (auto pair : keyMap) {
			if (pair.second.first == current && 
				pair.second.second == last) {
				toolMode = pair.first;
				return true;
			}
		}
	}
	else {
		for (auto pair : keyMap) {	// only has acitave button
			if (pair.second.second == last) {
				toolMode = pair.first;
				return true;
			}
		}
	}
	
	// nothing match
	return false;
}