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


void Camera::translate(glm::vec3 vec)
{
	translation = glm::translate(translation, vec);
    lookPos = lookPos + vec;
}


void Camera::rotate(float deg, glm::vec3 axis, glm::vec3 pivot/* = glm::vec3(1.0f)*/)
{
	glm::vec3 axis_normalized = glm::normalize(axis);

	// has pivot: rotate both pos & lookPos, this will orbit around pivot
	if (pivot != glm::vec3(1.0f)) {
        glm::mat4 posMat = getModelMat();
        glm::vec3 pos(posMat[3][0], posMat[3][1], posMat[3][2]);
        glm::vec3 offset = pos - pivot;
        glm::mat4 rot = glm::translate(glm::mat4(1.0f), offset);
		rot = glm::rotate(rot, glm::radians(deg), axis_normalized);
        rot = glm::translate(rot, -offset);
        translation = glm::translate(translation, glm::vec3(rot[3][0], rot[3][1], rot[3][2]));

        offset = lookPos - pivot;
        rot = glm::translate(glm::mat4(1.0f), offset);
		rot = glm::rotate(rot, glm::radians(deg), axis_normalized);
        rot = glm::translate(rot, -offset);
        glm::mat4 lookPosMat = glm::translate(glm::mat4(1.0f), lookPos);
        lookPosMat = glm::translate(lookPosMat, glm::vec3(rot[3][0], rot[3][1], rot[3][2]));
        lookPos = glm::vec3(lookPosMat[3][0], lookPosMat[3][1], lookPosMat[3][2]);
    }
	// no pivot: rotate only lookPos, this will look around but not moved
	else {
        glm::mat4 posMat = getModelMat();
        glm::vec3 pos(posMat[3][0], posMat[3][1], posMat[3][2]);
        glm::vec3 offset = lookPos - pos;
        glm::mat4 rot = glm::translate(glm::mat4(1.0f), offset);
		rot = glm::rotate(rot, glm::radians(deg), axis_normalized);
        rot = glm::translate(rot, -offset);
        glm::mat4 lookPosMat = glm::translate(glm::mat4(1.0f), lookPos);
        lookPosMat = glm::translate(lookPosMat, glm::vec3(rot[3][0], rot[3][1], rot[3][2]));
        lookPos = glm::vec3(lookPosMat[3][0], lookPosMat[3][1], lookPosMat[3][2]);
	}
}


void Camera::zoom(int direction)
{
    // move camera toward its face direction
	glm::vec3 dir = (float)direction * getDirection();
	glm::vec3 mov = SCALE_SENSITIVITY * dir;
	translate(mov);
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
}


void Camera::orbit(float distance, int xRight, int yDown)
{
    // rotate camera with the center point
    glm::mat4 posMat = getModelMat();
    glm::vec3 pivot =  glm::vec3(posMat[3][0], posMat[3][1], posMat[3][2])
        + distance * getDirection();
    rotate(ORBIT_SENSITIVITY * (float)xRight, UP_VECTOR, pivot);

    glm::vec3 right = glm::normalize(
        glm::cross(getDirection(), UP_VECTOR));
    rotate(ORBIT_SENSITIVITY * (float)yDown, right, pivot);
}


glm::mat4 Camera::getViewMat()
{
    glm::mat4 posMat = getModelMat();
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
    glm::mat4 posMat = getModelMat();
    glm::vec3 pos = glm::vec3(posMat[3][0], posMat[3][1], posMat[3][2]);
    
    return glm::normalize(lookPos - pos);
}


