#pragma once

#include "GLEW/glew.h"
#include "Shader.h"
#include "GLM/glm_996/mat4x4.hpp"


class ShaderProgram
{
public:
    ShaderProgram();
    ~ShaderProgram();
    void addShader(Shader &shader);
    bool compile();
    void bind();
    void unbind();
    void setUniformMat4(const char *name, glm::mat4 matrix);
    void setUniform1i(const char *name, GLint val);
    void setUniform1f(const char *name, GLfloat val);

private:
    GLint getUniform(const char *name);
    GLuint id;
};