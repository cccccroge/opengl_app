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

    void zoom(int direction);
    void pan(int xRight, int yDown);
    void move(const char dir);
    void orbit(float distance, int xRight, int yDown);
    void lookAround(int xRight, int yDown);

    glm::mat4 getViewMat();
    glm::mat4 getProjMat();
    
private:
    PROJECTION_TYPE proj_type;
    SceneObject lookPosObj;
    SceneObject rightDirObj;
    SceneObject upDirObj;

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

private:
    glm::vec3 getDirection(const char which);
    glm::vec3 getPos();
    glm::vec3 getLookPos();
    glm::vec3 getRightPos();
    glm::vec3 getUpPos();
};