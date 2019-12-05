#pragma once

#include "GLM/glm_996/vec3.hpp"
#include "GLM/glm_996/vec2.hpp"
#include <bitset>


class Vertex
{
public:
	Vertex(const glm::vec3 &pos, const glm::vec3 &normal, 
		const glm::vec2 &texCoord);
	Vertex(const glm::vec2 &pos2, const glm::vec3 &texCoord);
	Vertex();

	int getStride();
	int getOffset(const int index);
	

private:
	/* start from lower bit,
	   pattern '0101' -> enable position and normal */
	std::bitset<3> attrib_enabled;

    glm::vec3 position;
	glm::vec2 position2;
	glm::vec3 normal;
	glm::vec2 texture_coordinate;
};