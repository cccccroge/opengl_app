#include "ShaderProgram.h"
#include <iostream>
#include "GLM/glm_996/gtc/type_ptr.hpp"

ShaderProgram::ShaderProgram()
{
    id = glCreateProgram();
}


ShaderProgram::~ShaderProgram()
{
    glDeleteProgram(id);
}


void ShaderProgram::addShader(Shader &shader)
{
    if (!shader.getStatus()) {
        std::cout << "Try to attach invalid shader to program" << std::endl;
        return;
    }

    glAttachShader(id, shader.getId());
}


bool ShaderProgram::compile()
{
    glLinkProgram(id);

    GLint success;
    glGetProgramiv(id, GL_LINK_STATUS, &success);

    if (success != GL_TRUE)
    {
        GLsizei length;
        glGetProgramiv(id, GL_INFO_LOG_LENGTH, &length);
        GLchar info[length];
        glGetProgramInfoLog(id, length, nullptr, info);
        
        std::cout << "Failed to link program:" << std::endl;
        std::cout << info << std::endl;

        return false;
    }

    return true;
}


void ShaderProgram::bind()
{
    glUseProgram(id);
}


GLint ShaderProgram::getUniform(const char *name)
{
    return glGetUniformLocation(id, name);
}


void ShaderProgram::setUniformMat4(const char *name, glm::mat4 matrix)
{
    glUniformMatrix4fv(getUniform(name), 1, false, glm::value_ptr(matrix));
}
