#pragma once


void onMenuTriggered(int id);
void onDisplayRefresh(void);
void onWindowReshaped(int width, int height);
void onTimerExpired(int value);
void onKeyboardPressed(unsigned char key, int x, int y);
void onSpecialkeysPressed(int key, int x, int y);
void onMousePressed(int button, int state, int x, int y);
void onWindowClosed(void);