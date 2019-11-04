#include "GLEW/glew.h"
#include "init.h"
#include "freeGLUT/freeglut.h"
#include "callback.h"
#include <iostream>

int initGlutContext(int argc, char *argv[])
{
	glutInitContextVersion(CONTEXT_VER_MAJOR, CONTEXT_VER_MINOR);
	glutInitContextProfile(GLUT_CORE_PROFILE);
	glutInit(&argc, argv);

    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH | GLUT_MULTISAMPLE);
	int mainwindow_width = 1024;
	int mainwindow_height = 576;
	int center_x = (glutGet(GLUT_SCREEN_WIDTH) - mainwindow_width) / 2;
	int center_y = (glutGet(GLUT_SCREEN_HEIGHT) - mainwindow_height) / 2;
	glutInitWindowSize(mainwindow_width, mainwindow_height);
	glutInitWindowPosition(center_x, center_y);

	return glutCreateWindow("My Robot");
}

void initGlew(void)
{
	GLenum err = glewInit();
	if (err != GLEW_OK) {
		std::cout << glewGetErrorString(err) << std::endl;
	}
}

void createMenu(void)
{
	int menu_main = glutCreateMenu(onMenuTriggered);
	int menu_timer = glutCreateMenu(onMenuTriggered);
	int menu_animation = glutCreateMenu(onMenuTriggered);

	glutSetMenu(menu_main);
	glutAddSubMenu("Timer", menu_timer);
	glutAddSubMenu("Animation", menu_animation);
	glutAddMenuEntry("Exit", MENU_EXIT);

	glutSetMenu(menu_timer);
	glutAddMenuEntry("Start", MENU_TIMER_START);
	glutAddMenuEntry("Stop", MENU_TIMER_STOP);

	glutSetMenu(menu_animation);						
	glutAddMenuEntry("Idle", MENU_IDLE);		
	glutAddMenuEntry("Superman!", MENU_SUPERMAN);		

	glutSetMenu(menu_main);
	glutAttachMenu(MENU_TRIGGER_BUTTON);
}

void registerCallbacks(void)
{
	glutDisplayFunc(onDisplayRefresh);
	glutReshapeFunc(onWindowReshaped);
	glutKeyboardFunc(onKeyboardPressed);
	glutSpecialFunc(onSpecialkeysPressed);
	glutCloseFunc(onWindowClosed);
	glutMouseFunc(onMousePressed);
	glutMouseWheelFunc(onMouseWheelSpinned);
}