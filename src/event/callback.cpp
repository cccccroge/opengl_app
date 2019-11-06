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
std::map<std::string, bool> btnsPressed;
std::set<std::string> pressedBtnSet;

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
	if (!btnsPressed[keyStr]) {
		pressedBtnSet.insert(keyStr);
		std::cout << "set: ";
		for (auto str : pressedBtnSet) {
			std::cout << str << " ";
		}
		std::cout << std::endl;
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
	pressedBtnSet.erase(keyStr);
	std::cout << "set: ";
	for (auto str : pressedBtnSet) {
		std::cout << str << " ";
	}
	std::cout << std::endl;
	
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
	if (!btnsPressed[keyStr]) {
		pressedBtnSet.insert(keyStr);
		std::cout << "set: ";
		for (auto str : pressedBtnSet) {
			std::cout << str << " ";
		}
		std::cout << std::endl;
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
	pressedBtnSet.erase(keyStr);
	std::cout << "set: ";
	for (auto str : pressedBtnSet) {
		std::cout << str << " ";
	}
	std::cout << std::endl;

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
		if (!btnsPressed[keyStr]) {
			pressedBtnSet.insert(keyStr);
			std::cout << "set: ";
			for (auto str : pressedBtnSet) {
				std::cout << str << " ";
			}
			std::cout << std::endl;
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
		pressedBtnSet.erase(keyStr);
		std::cout << "set: ";
		for (auto str : pressedBtnSet) {
			std::cout << str << " ";
		}
		std::cout << std::endl;

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
		toolMode = TOOL_MODE::NONE;
		return false;
	}

	// activate if find
	std::set<std::string> exceptLast = pressedBtnSet;
	exceptLast.erase(last);
	std::pair<std::set<std::string>, std::string> currentPair = { exceptLast, last };

	if (keyMap.find(currentPair) != keyMap.end()) {
		toolMode = keyMap[currentPair];
		return true;
	}
	
	// nothing match
	return false;
}