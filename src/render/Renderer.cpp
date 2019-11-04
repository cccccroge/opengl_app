#include "Renderer.h"
#include "freeGLUT/freeglut.h"
#include "../utils.h"
#include "../global.h"
#include <iostream>

Renderer::Renderer() : m_camera(NULL)
{
    glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
    glEnable(GL_MULTISAMPLE);
}


Renderer::~Renderer()
{
    
}


void Renderer::setCamera(Camera &cam)
{
    m_camera = &cam;
}


void Renderer::addMesh(Mesh &mesh)
{
    mesh_vec.push_back(&mesh);
}


void Renderer::RenderAll()
{
    // Clear display buffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Bind Program
    global::program->bind();

    for (auto meshPtr : mesh_vec) {
        // change MVP in program
        glm::mat4 model = (*meshPtr).getModelMat();
        glm::mat4 view = (*m_camera).getViewMat();
        glm::mat4 proj = (*m_camera).getProjMat();
        global::program->setUniformMat4("um4mvp", proj * view * model);

        // bind object
        (*meshPtr).bind();

        // issue draw call
        GLsizei count = (*meshPtr).getShape().indexCount;
	    glDrawElements(GL_TRIANGLES, count, GL_UNSIGNED_INT, 0);
	}

    glutSwapBuffers();
	//printGLError();
}
