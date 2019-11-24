#pragma once

#include "GLM/glm_996/vec3.hpp"
#include "GLM/glm_996/vec2.hpp"


/* For now, assume each vertex has fixed format:
   [position(vec3), normal(vec3), textCoord(vec3)] */
class Vertex
{
public:
	Vertex(const glm::vec3 &pos, const glm::vec3 &normal, 
		const glm::vec2 &texCoord);
	

private:
    glm::vec3 position;
	glm::vec3 normal;
	glm::vec2 texture_coordinate;
};