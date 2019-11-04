#pragma once

#include "GLEW/glew.h"
#include "../scene/Mesh.h"
#include "../scene/Camera.h"
#include <vector>


class Renderer
{
public:
    Renderer();
    ~Renderer();
    void setCamera(Camera &cam);
    void addMesh(Mesh &mesh);
    void RenderAll();

private:
    Camera *m_camera;
    std::vector<Mesh *> mesh_vec;
};

