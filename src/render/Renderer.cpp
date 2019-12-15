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
    

    // draw all models
    glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);

    global::program_model->bind();

    for (auto modelPtr : model_vec) {
        // change MVP in program
        glm::mat4 model = modelPtr->getModelMat();
        glm::mat4 view = m_camera->getViewMat();
        glm::mat4 proj = m_camera->getProjMat();
        glm::vec3 cameraPos = m_camera->getPos();
        global::program_model->setUniformMat4("mvpMatrix", proj * view * model);
        global::program_model->setUniformMat4("mMatrix", model);
        global::program_model->setUniformVec3("viewPos", cameraPos);

        // bind mesh and draw
        for (auto meshPtr : modelPtr->getMeshes()) {
            skybox->getTexture().bind();  // use in enviroment mapping
            meshPtr->bind(*global::program_model, "tex");
	        glDrawElements(GL_TRIANGLES, meshPtr->getIndicesNum(),
                GL_UNSIGNED_INT, 0);
        }
	}

    // draw sky box
    glDepthMask(GL_FALSE);

    global::program_skybox->bind();
    glm::mat4 model = skybox->getModelMat();
    glm::mat4 view = glm::mat4( // drop transformation for skybox so that it won't move
        glm::mat3(m_camera->getViewMat()));
    glm::mat4 proj = m_camera->getProjMat();
    global::program_skybox->setUniformMat4("um4mvp", proj * view * model);
    skybox->bind();
    glDrawArrays(GL_TRIANGLES, 0, 36);

    glDepthMask(GL_TRUE);


    /* Second pass */
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    glDisable(GL_DEPTH_TEST);

    global::program_posteffect->bind();
    global::postEffectBuffer->bindScreen();
    glDrawArrays(GL_TRIANGLES, 0, 6);


    /* Finish all draw calls, now flip swap buffer */
    glutSwapBuffers();
	//printGLError();
}
