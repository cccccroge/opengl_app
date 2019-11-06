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


void Camera::zoom(int direction)
{
    // move camera toward its face direction
	glm::vec3 dir = (float)direction * getDirection();
	glm::vec3 mov = SCALE_SENSITIVITY * dir;
	translate(mov[0], mov[1], mov[2]);
	setLookPos(getLookPos() + mov);	// update cam's lookPos
}


void Camera::pan(int xRight, int yDown)
{
    // move camera toward the vectors orthogonal to its face direction
    glm::vec3 right = glm::normalize(
        glm::cross(getDirection(), UP_VECTOR));
    glm::vec3 down = glm::normalize(
        glm::cross(getDirection(), right));

    glm::vec3 movement = -PAN_SENSITIVITY * 
        ((float)xRight * right + (float)yDown * down);
    translate(movement);
    setLookPos(getLookPos() + movement);	// update cam's lookPos
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


