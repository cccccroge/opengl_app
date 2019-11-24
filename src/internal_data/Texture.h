#pragma once

#include <string>
#include "GLEW/glew.h"
#include "../render/ShaderProgram.h"
#include <string>


class Texture
{
public:
    Texture(const char *path);
    void setUp();
    void bind(ShaderProgram &program, const std::string tex_prefix, 
        const int index);

    inline const char* getPath() { return path; }

private:
    int width;
    int height;
    unsigned char *data;
    std::string type;
    const char *path;   // absolute path get from Model

    GLuint tbo;
};