#include "Mesh.h"

Mesh::Mesh() : vao(0), vbo(0), ebo(0)
{
    // we can't call setUp() unitil assimp importer
    // from model get the actual data
}


void Mesh::setUp()
{
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    // Vertex
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex),
        &vertices[0], GL_STATIC_DRAW);
    //glBindBuffer(GL_ARRAY_BUFFER, 0);

    /* For now, assume each vertex has fixed format:
   [position(vec3), normal(vec3), textCoord(vec2)] */
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), 
        (const void *)0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), 
        (const void *)(3* sizeof(float)));
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), 
        (const void *)(6* sizeof(float)));

    // Index
    glGenBuffers(1, &ebo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint),
        &indices[0], GL_STATIC_DRAW);
    //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    glBindVertexArray(0);
}


void Mesh::bind(ShaderProgram &program, const std::string tex_prefix)
{
    for (int i = 0; i < textures.size(); ++i) {
        textures[i].bind(program, tex_prefix, i);
    }

    glBindVertexArray(vao);
}