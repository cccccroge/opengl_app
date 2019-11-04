#pragma once

#include "GLEW/glew.h"
#include "GLM/glm_996/vec3.hpp"
#include "TinyOBJ/tiny_obj_loader.h"
#include "../render/ShaderProgram.h"
#include "SceneObject.h"
#include "Camera.h"
#include <vector>


class Shape	// TODO: move to renderer
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


class Mesh : public SceneObject
{
public:
	Mesh();
    Mesh(const char *obj_file, 
		glm::vec3 pos = glm::vec3(0.0f, 0.0f, 0.0f));
	void sendRendering();	// TODO: move to renderer
	void bind();
	void attachProgram(ShaderProgram &program);

	inline ShaderProgram& getProgram() { return *m_program; }
	inline Shape& getShape() { return m_shape; }

private:
    Shape m_shape;	// TODO: move to renderer
	ShaderProgram *m_program;

    std::vector<tinyobj::shape_t> shapes;
	std::vector<tinyobj::material_t> materials;
};