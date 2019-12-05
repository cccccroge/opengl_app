#include "Vertex.h"
#include <string>


Vertex::Vertex(const glm::vec3 &pos, const glm::vec3 &normal, 
		const glm::vec2 &texCoord):
        position(pos), position2(), normal(normal), 
        texture_coordinate(texCoord),
        attrib_enabled(std::string("1011"))
{
    
}


Vertex::Vertex(const glm::vec2 &pos2, const glm::vec2 &texCoord) : 
    position2(pos2), texture_coordinate(texCoord),
    attrib_enabled(std::string("0101"))
{
    
}


Vertex::Vertex() : position(), position2(), normal(), 
    texture_coordinate(), attrib_enabled()
{

}


int Vertex::getOffset(const int index)
{
    
}


int Vertex::getStride()
{
    int stride = 0;

    if (attrib_enabled[0]) {
        stride += 3 * sizeof(float);
    }
    else if (attrib_enabled[1]) {
        stride += 2 * sizeof(float);
    }
    else if (attrib_enabled[2]) {
        stride += 3 * sizeof(float);
    }
    else if (attrib_enabled[3]) {
        stride += 2 * sizeof(float);
    }

    return stride;
}

	