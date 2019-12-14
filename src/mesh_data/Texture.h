#pragma once

#include <string>
#include "GLEW/glew.h"
#include "../render/ShaderProgram.h"
#include <string>


class Texture
{
public:
    Texture(const char *path);
    Texture(const int width, const int height);
    ~Texture();

    void setUp();
    void bind(ShaderProgram &program, const std::string tex_prefix, 
        const int index);
    void bind();

    inline const char* getPath() { return path; }
    inline GLuint getTbo() { return tbo; }

private:
    int width;
    int height;
    unsigned char *data;
    std::string type;
    const char *path;   // absolute path get from Model

    GLuint tbo;
};