#pragma once

#include "GLEW/glew.h"
#include "GLM/glm_996/vec3.hpp"
#include "TinyOBJ/tiny_obj_loader.h"
#include "../render/ShaderProgram.h"
#include "SceneObject.h"
#include "Camera.h"
#include <vector>


class Shape
{
public:
	GLuint vao;			// vertex array object
	GLuint vbo;			// vertex buffer object
	GLuint vboTex;		// vertex buffer object of texture
	GLuint ebo;			

	GLuint p_normal;
	int materialId;
	int indexCount;
	GLuint m_texture;
};


class Model : public SceneObject
{
public:
	Model();
    Model(const char *obj_file, 
		glm::vec3 pos = glm::vec3(0.0f, 0.0f, 0.0f));
	void bind();

	inline Shape& getShape() { return m_shape; }

private:
    Shape m_shape;
};