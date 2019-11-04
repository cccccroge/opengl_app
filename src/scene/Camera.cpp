#include "Camera.h"
#include "../init.h"

#include "GLM/glm_996/ext/matrix_transform.hpp"
#include "GLM/glm_996/ext/matrix_clip_space.hpp"
#include "../global.h"
#include <iostream>


Camera::Camera() : SceneObject(glm::vec3(0.0f, 0.0f, 0.0f))
{
    
}


Camera::Camera(PROJECTION_TYPE type, std::vector<float> boundary, 
    glm::vec3 pos, glm::vec3 lookPos, float fov) :
        proj_type(type), near(boundary[0]), far(boundary[1]), 
        SceneObject(pos), lookPos(lookPos), fov(glm::radians(fov))
{
    if (proj_type == PROJECTION_TYPE::ORTHOGONAL) {
        left = boundary[2];
        right = boundary[3];
        bottom = boundary[4];
        top = boundary[5];
    }
}


glm::mat4 Camera::getViewMat()
{
    glm::mat4 posMat = getTranslation() * getOriginal();
    glm::vec3 pos(posMat[3][0], posMat[3][1], posMat[3][2]);
    return glm::lookAt(pos, lookPos, UP_VECTOR);
}


glm::mat4 Camera::getProjMat()
{
    if (proj_type == PROJECTION_TYPE::PERSPECTIVE) {
        float ratio = global::renderWidth / global::renderHeight;
        return glm::perspective(fov, ratio, near, far);
    }
    else if (proj_type == PROJECTION_TYPE::ORTHOGONAL) {
        return glm::ortho(left, right, bottom, top, near, far);
    }
    else {
        std::cout << "Can't generate correct projection matrix" << std::endl;
        return glm::mat4(1.0f);
    }
}


glm::vec3 Camera::getDirection()
{
    glm::mat4 posMat = getTranslation() * getOriginal();
    glm::vec3 pos = glm::vec3(posMat[3][0], posMat[3][1], posMat[3][2]);
    
    return glm::normalize(lookPos - pos);
}


