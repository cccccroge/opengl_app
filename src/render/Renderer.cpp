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
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC1_ALPHA);
    //glEnable(GL_CULL_FACE);
}


Renderer::~Renderer()
{
    
}


void Renderer::setCamera(Camera &cam)
{
    m_camera = &cam;
}


void Renderer::addModel(Model &model)
{
    model_vec.push_back(&model);
}


void Renderer::RenderAll()
{
    // Clear display buffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Bind Program
    global::program->bind();

    for (auto modelPtr : model_vec) {
        // change MVP in program
        glm::mat4 model = (*modelPtr).getModelMat();
        glm::mat4 view = (*m_camera).getViewMat();
        glm::mat4 proj = (*m_camera).getProjMat();
        global::program->setUniformMat4("um4mvp", proj * view * model);

        // bind mesh and draw
        for (auto mesh : modelPtr->getMeshes()) {
            mesh.bind(*global::program, "tex");
	        glDrawElements(GL_TRIANGLES, mesh.getIndices().size(), 
                GL_UNSIGNED_INT, 0);
        }
	}

    glutSwapBuffers();
	//printGLError();
}
