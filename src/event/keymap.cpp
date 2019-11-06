#include "keymap.h"
#include <iostream>


std::map<TOOL_MODE, std::pair<std::set<std::string>, std::string> > keyMap = {
        { 
            TOOL_MODE::PAN, { { "shift_L" }, "mouse_M" }
        },
        { 
            TOOL_MODE::ORBIT, { std::set<std::string>(), "mouse_M" }
        },
        /*{
             TOOL_MODE::ZOOM, { {?} } // ignore, GLUT treat mouse wheel as seperated callback
        },*/
    };

std::string btn2str(int GLUT_BUTTON)
{
    if (GLUT_BUTTON == GLUT_KEY_SHIFT_L)
        return "shift_L";
    else if (GLUT_BUTTON == GLUT_KEY_SHIFT_R)
        return "shift_R";
    else if (GLUT_BUTTON == GLUT_MIDDLE_BUTTON)
        return "mouse_M";
    else if (GLUT_BUTTON == GLUT_LEFT_BUTTON)
        return "mouse_L";
    else if (GLUT_BUTTON == GLUT_RIGHT_BUTTON)
        return "mouse_R";
    else {
        std::cout << "can't convert GLUT_BUTTON to string" << std::endl;
        return "";
    }
        
}