#pragma once

#include "GLM/glm_996/vec3.hpp"
#include "GLM/glm_996/vec2.hpp"


class VertexPNT
{
public:
	VertexPNT(const glm::vec3 &pos, const glm::vec3 &normal, 
		const glm::vec2 &texCoord);

private:
    glm::vec3 position;
	glm::vec3 normal;
	glm::vec2 texture_coordinate;
};

class VertexP2T
{
public:
	VertexP2T(const glm::vec2 &pos2, const glm::vec2 &texCoord);
	
private:
	glm::vec2 position2d;
	glm::vec2 texture_coordinate;
};

