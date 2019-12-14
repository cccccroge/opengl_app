#pragma once

#include "GLEW/glew.h"
#include "../scene/Model.h"
#include "../scene/Camera.h"
#include "../scene/Skybox.h"
#include <vector>


class Renderer
{
public:
    Renderer();
    ~Renderer();
    void setCamera(Camera &cam);
    void addModel(Model &model);
    void addSkybox(Skybox &skybox);
    void RenderAll();

    inline Camera* getCamera() { return m_camera; }

private:
    Camera *m_camera;
    std::vector<Model *> model_vec;
    Skybox *skybox;
};

