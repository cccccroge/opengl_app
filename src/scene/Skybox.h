#pragma once

#include "SceneObject.h"
#include <vector>
#include <string>
#include "../mesh_data/Mesh.h"
#include "../mesh_data/CubemapTexture.h"


/* This class serve as task specific SceneObject (render as skybox as background) */
class Skybox : public SceneObject
{
public:
    Skybox(const std::vector<std::string> images);
    ~Skybox();

    void bind();
    void unbind();

private:
    Mesh *cube_mesh;
    CubemapTexture cubemap_tex;
};