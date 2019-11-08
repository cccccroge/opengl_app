#include "Camera.h"
#include "../init.h"

#include "GLM/glm_996/ext/matrix_transform.hpp"
#include "GLM/glm_996/ext/matrix_clip_space.hpp"
#include "GLM/glm_996/gtx/projection.hpp"
#include "../global.h"
#include <iostream>


Camera::Camera() : SceneObject(glm::vec3(0.0f, 0.0f, 0.0f))
{
    
}


Camera::Camera(PROJECTION_TYPE type, std::vector<float> boundary, 
    glm::vec3 position, glm::vec3 lookPos, float fov) :
        proj_type(type), lookPosObj(), rightDirObj(), upDirObj(), 
        fov(glm::radians(fov)), near(boundary[0]), far(boundary[1]), 
        SceneObject()
{
    if (proj_type == PROJECTION_TYPE::ORTHOGONAL) {
        left = boundary[2];
        right = boundary[3];
        bottom = boundary[4];
        top = boundary[5];
    }

    // translate to position
    translate(position);

    // setup auxillary objects
    lookPosObj.translate(lookPos);

    glm::vec3 rightDir = glm::normalize(
        glm::cross(lookPos - position, UP_VECTOR));
    rightDirObj.translate(position);
    rightDirObj.translate(rightDir);

    glm::vec3 upDir = glm::normalize(
        glm::cross(rightDir, lookPos - position));
    upDirObj.translate(position);
    upDirObj.translate(upDir);
}


void Camera::zoom(int direction)
{
    // move camera toward its face direction
	glm::vec3 dir = (float)direction * getDirection('f');
	glm::vec3 mov = SCALE_SENSITIVITY * dir;
	translate(mov);
    lookPosObj.translate(mov);
    rightDirObj.translate(mov);
    upDirObj.translate(mov);
}


void Camera::pan(int xRight, int yDown)
{
    // move camera toward the vectors orthogonal to its face direction
    glm::vec3 right = getDirection('r');
    glm::vec3 down = glm::normalize(
        glm::cross(getDirection('f'), right));

    glm::vec3 mov = -PAN_SENSITIVITY * 
        ((float)xRight * right + (float)yDown * down);
    translate(mov);
    lookPosObj.translate(mov);
    rightDirObj.translate(mov);
    upDirObj.translate(mov);
}


void Camera::orbit(float distance, int xRight, int yDown)
{
    // rotate camera at the center point
    glm::vec3 pivot =  getPos() + distance * getDirection('f');
    float dx_right = ORBIT_SENSITIVITY * (float)xRight;
    float dy_down = ORBIT_SENSITIVITY * (float)yDown;
    glm::vec3 rightDir = getDirection('r');

    rotatePivot(dx_right, UP_VECTOR, pivot);
    rotatePivot(dy_down, rightDir, pivot);
    lookPosObj.rotatePivot(dx_right, UP_VECTOR, pivot);
    lookPosObj.rotatePivot(dy_down, rightDir, pivot);
    rightDirObj.rotatePivot(dx_right, UP_VECTOR, pivot);
    rightDirObj.rotatePivot(dy_down, rightDir, pivot);
    upDirObj.rotatePivot(dx_right, UP_VECTOR, pivot);
    upDirObj.rotatePivot(dy_down, rightDir, pivot);
}


glm::mat4 Camera::getViewMat()
{
    return glm::lookAt(getPos(), getLookPos(), getDirection('u'));
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


glm::vec3 Camera::getDirection(const char which)
{
    if (which == 'f') {
        return glm::normalize(getLookPos() - getPos());
    }
    else if (which == 'r') {
        return glm::normalize(getRightPos() - getPos());
    }
    else if (which == 'u') {
        return glm::normalize(getUpPos() - getPos());
    }
}


glm::vec3 Camera::getPos()
{
    return glm::vec3(getModelMat()[3]);
}


glm::vec3 Camera::getLookPos()
{
    return glm::vec3(lookPosObj.getModelMat()[3]);
}


glm::vec3 Camera::getRightPos()
{
    return glm::vec3(rightDirObj.getModelMat()[3]);
}


glm::vec3 Camera::getUpPos()
{
    return glm::vec3(upDirObj.getModelMat()[3]);
}

