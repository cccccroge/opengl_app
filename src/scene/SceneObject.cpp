#include "SceneObject.h"
#include "GLM/glm_996/ext/matrix_transform.hpp"
#include "GLM/glm_996/geometric.hpp"


SceneObject::SceneObject(glm::vec3 pos) : 
	original(glm::mat4(1.0f)), 
    translation(glm::mat4(1.0f)),
	rotation(glm::mat4(1.0f)),
    scaling(glm::mat4(1.0f)),
	translation_p(glm::mat4(1.0f)),
	rotation_p(glm::mat4(1.0f)),
    scaling_p(glm::mat4(1.0f)),
	parent(NULL)
{
	// initial postion provided
	if (!glm::all(glm::equal(pos, glm::vec3(0.0f, 0.0f, 0.0f)))) {
		original = glm::translate(original, pos);
	}
}


glm::mat4 SceneObject::getModelMat()
{
	if (parent != NULL) {
		return parent->getModelMat() * (translation_p * original) * scaling_p * rotation_p;
	}
	else {
		return (translation * original) * scaling * rotation;
	}
}


void SceneObject::translate(float x, float y, float z)
{
	if (parent != NULL) {
		translation_p = glm::translate(translation_p, glm::vec3(x, y, z));
	}
	else {
		translation = glm::translate(translation, glm::vec3(x, y, z));
	}
}


void SceneObject::translate(glm::vec3 vec)
{
	if (parent != NULL) {
		translation_p = glm::translate(translation_p, vec);
	}
	else {
		translation = glm::translate(translation, vec);
	}
}


void SceneObject::rotate(float deg, std::vector<float> axis, glm::vec3 pivot/* = glm::vec3(1.0)*/)
{
/* 	glm::mat4 newRotation(1.0f);

	// pivot provided, offset matrix before rotate
	if (pivot != glm::vec3(1.0f)) {
		glm::mat4 posMat = translation * original;
		glm::vec3 pos(posMat[3][0], posMat[3][1], posMat[3][2]);
		glm::vec3 offset = pos - pivot;
		newRotation = glm::translate(newRotation, offset);
	} */

	glm::vec3 axis_normalized = 
		glm::normalize(glm::vec3(axis[0], axis[1], axis[2]));

	if (parent != NULL) {
		rotation_p = glm::rotate(rotation_p, glm::radians(deg), axis_normalized);
	}
	else {
		rotation = glm::rotate(rotation, glm::radians(deg), axis_normalized);
	}
	

}


void SceneObject::rotate(float deg, glm::vec3 axis, glm::vec3 pivot/* = glm::vec3(1.0f)*/)
{
	glm::vec3 axis_normalized = glm::normalize(axis);

	// has pivot: translate and rotate, and reversing the translation
	if (pivot != glm::vec3(1.0f)) {
		if (parent != NULL) {

		}
		else {
			glm::mat4 posMat = getModelMat();
			glm::vec3 offset = 
				glm::vec3(posMat[3][0], posMat[3][1], posMat[3][2]) - pivot;
			glm::mat4 r = glm::translate(glm::mat4(1.0f), offset);

			rotation = glm::rotate(r, glm::radians(deg), axis_normalized);
			rotation = glm::translate(glm::mat4(1.0f), -offset);
		}
		
	}
	// no pivot: rotate locally
	else {
		if (parent != NULL) {
			rotation_p = glm::rotate(rotation_p, glm::radians(deg), axis_normalized);
		}
		else {
			rotation = glm::rotate(rotation, glm::radians(deg), axis_normalized);
		}
	}
}


void SceneObject::scale(float x, float y, float z)
{
	if (parent != NULL) {
		scaling_p = glm::scale(scaling_p, glm::vec3(x, y, z));
	}
	else {
		scaling = glm::scale(scaling, glm::vec3(x, y, z));
	}
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

	// use new set of transformation
	translation_p = glm::inverse(parent->getTranslation()) * translation;
	rotation_p = glm::inverse(parent->getRotation()) * rotation;
	scaling_p = glm::inverse(parent->getScaling()) * scaling;
}


void SceneObject::clearParent()
{
/* 	translation = translation_p;
	rotation = rotation_p;
	scaling = scaling_p; */

	translation_p = glm::mat4(1.0f);
	rotation_p = glm::mat4(1.0f);
	scaling_p = glm::mat4(1.0f);

	parent = NULL;
}