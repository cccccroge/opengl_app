#pragma once

#include "GLM/glm_996/mat4x4.hpp"
#include "GLEW/glew.h"
#include <vector>


class SceneObject
{
public:
    SceneObject(glm::vec3 pos = glm::vec3(0.0f, 0.0f, 0.0f)); 
	glm::mat4 getModelMat();

	void translate(float x, float y, float z);
	void rotate(float deg, std::vector<float> axis);
	void scale(float x, float y, float z);
    void resetTransformation();

    void setParent(SceneObject &object);
    void clearParent();

    inline glm::mat4 getOriginal() { return original; }
    inline glm::mat4 getTranslation() { return translation; }

private:
    glm::mat4 original; // TODO: maybe split to world and local space?
    glm::mat4 translation;
    glm::mat4 rotation;
    glm::mat4 scaling;

protected:
    SceneObject *parent;
};