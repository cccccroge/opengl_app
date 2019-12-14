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

void Renderer::addSkybox(Skybox &_skybox)
{
    skybox = &_skybox;
}

void Renderer::RenderAll()
{
    /* First pass */
    global::postEffectBuffer->bindFrameBuffer();
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    

    // draw sky box
    glDepthMask(GL_FALSE);

    global::program_skybox->bind();
    glm::mat4 model = skybox->getModelMat();
    glm::mat4 view = glm::mat4(
        glm::mat3(m_camera->getViewMat()));  // drop transformation for skybox
    glm::mat4 proj = m_camera->getProjMat();
    global::program_skybox->setUniformMat4("um4mvp", proj * view * model);
    skybox->bind();
    glDrawArrays(GL_TRIANGLES, 0, 36);
    glDepthMask(GL_TRUE);


glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
    // draw all models
    /*global::program_first->bind();

    for (auto modelPtr : model_vec) {
        // change MVP in program
        glm::mat4 model = modelPtr->getModelMat();
        glm::mat4 view = m_camera->getViewMat();
        glm::mat4 proj = m_camera->getProjMat();
        global::program_first->setUniformMat4("um4mvp", proj * view * model);

        // bind mesh and draw
        for (auto meshPtr : modelPtr->getMeshes()) {
            meshPtr->bind(*global::program_first, "tex");
	        glDrawElements(GL_TRIANGLES, meshPtr->getIndicesNum(),
                GL_UNSIGNED_INT, 0);
        }
	}


    /* Second pass */
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    glDisable(GL_DEPTH_TEST);

    global::program_second->bind();
    global::postEffectBuffer->bindScreen();
    glDrawArrays(GL_TRIANGLES, 0, 6);


    /* Finish all draw calls, now flip swap buffer */
    glutSwapBuffers();
	//printGLError();
}
