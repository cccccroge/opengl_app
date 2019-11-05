#include "SceneObject.h"
#include "GLM/glm_996/ext/matrix_transform.hpp"
#include "GLM/glm_996/geometric.hpp"


SceneObject::SceneObject(glm::vec3 pos) : 
	original(glm::mat4(1.0f)), 
    translation(glm::mat4(1.0f)), rotation(glm::mat4(1.0f)), 
    scaling(glm::mat4(1.0f)),
	parent(NULL)
{
	// initial postion provided
	if (!glm::all(glm::equal(pos, glm::vec3(0.0f, 0.0f, 0.0f)))) {
		original = glm::translate(original, pos);
	}
}


glm::mat4 SceneObject::getModelMat()
{
	glm::mat4 currentMat = (translation * original) * scaling * rotation;

	if (parent != NULL) {
		glm::mat4 parentMat = parent->getModelMat();
		return parentMat * currentMat;
	}

	return currentMat;
}


void SceneObject::translate(float x, float y, float z)
{
	translation = glm::translate(translation, glm::vec3(x, y, z));
}


void SceneObject::translate(glm::vec3 vec)
{
	translation = glm::translate(translation, vec);
}


void SceneObject::rotate(float deg, std::vector<float> axis)
{
	glm::vec3 axis_normalized = 
		glm::normalize(glm::vec3(axis[0], axis[1], axis[2]));
	rotation = glm::rotate(rotation, glm::radians(deg), axis_normalized);
}


void SceneObject::scale(float x, float y, float z)
{
	scaling = glm::scale(scaling, glm::vec3(x, y, z));
}


void SceneObject::resetTransformation()
{
	translation = glm::mat4(1.0f);
	rotation = glm::mat4(1.0f);
	scaling = glm::mat4(1.0f);
}


void SceneObject::setParent(SceneObject &object)
{
	parent = &object;

	// recalculate original
	original = glm::inverse(parent->getModelMat()) * original;
}


void SceneObject::clearParent()
{
	// recalculate original to get back
	original = parent->getModelMat() * original;

	parent = NULL;
}