#pragma once

#include "freeGLUT/freeglut.h"
#include <string>
#include <map>
#include <set>


enum class TOOL_MODE {
	NONE,
	ZOOM,
	PAN,
	ORBIT
};

/* map [TOOL_MODE] to [Pair], each pair has a pressed button set
   and an activate button */
extern std::map<TOOL_MODE, std::pair<std::set<std::string>, std::string> > keyMap;

std::string btn2str(int GLUT_BUTTON);