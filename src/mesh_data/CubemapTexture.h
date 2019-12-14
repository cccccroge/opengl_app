#pragma once

#include "GLEW/glew.h"
#include <vector>
#include <string>


class CubemapTexture
{
public:
    CubemapTexture(const std::vector<std::string> paths);
    ~CubemapTexture();

    void bind();
    void unbind();


private:
    std::vector<std::string> paths;
    GLuint tbo;
};