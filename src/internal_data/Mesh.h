#pragma once

#include "GLEW/glew.h"
#include <vector>
#include "Vertex.h"
#include "Texture.h"
#include "../scene/SceneObject.h"


/* a Mesh act like a node in Assimp */
class Mesh : public SceneObject
{
public:
    Mesh();
    inline std::vector<Vertex>& getVertices() { return vertices; }
    inline std::vector<GLuint>& getIndices() { return indices; }
    inline std::vector<Texture>& getTextures() { return textures; }
    void setUp();
    void bind(ShaderProgram &program, const std::string tex_prefix);

private:
    std::vector<Vertex> vertices;
    std::vector<GLuint> indices;
    std::vector<Texture> textures;

    // assume each vertex in a Mesh has same format
    // so we use the same vao to render
    GLuint vao;
    GLuint vbo;

    GLuint ebo;
};