#pragma once

#include "SceneObject.h"
#include "GLM/glm_996/mat4x4.hpp"
#include "GLM/glm_996/trigonometric.hpp"
#include <vector>


enum class PROJECTION_TYPE
{
    PERSPECTIVE, ORTHOGONAL
};


class Camera : public SceneObject
{
public:
    Camera();
    Camera(PROJECTION_TYPE type, std::vector<float> boundary, 
        glm::vec3 pos = glm::vec3(0.0f, 0.0f, 0.0f), 
        glm::vec3 lookPos = glm::vec3(0.0f, 0.0f, 0.0f), 
        float fov = glm::radians(60.0f));

    glm::mat4 getViewMat();
    glm::mat4 getProjMat();

private:
    PROJECTION_TYPE proj_type;
    glm::vec3 lookPos;

    // used in PERSPECTIVE
    float fov;  // rads

    // means near/far in PERSPECTIVE, or zNear/zFar in ORTHOGONAL
    float near;
    float far;

    // used in ORTHOGONAL
    float left;
    float right;
    float bottom;
    float top;
};