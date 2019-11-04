#include "Mesh.h"
#include "../utils.h"

Mesh::Mesh() : SceneObject(glm::vec3(0.0f, 0.0f, 0.0f))
{

}


Mesh::Mesh(const char *obj_file, glm::vec3 pos) : SceneObject(pos), 
	m_shape(Shape())
{
    std::string err;
	tinyobj::LoadObj(this->shapes, this->materials, err, obj_file);

	if(err.size()>0)
	{
		printf("Load Models Fail! Please check the solution path\n");
		return;
	}
	
	printf("Load Models Success ! Shapes size %d Maerial size %d\n", shapes.size(), materials.size());
}


void Mesh::sendRendering()
{
	for(int i = 0; i < shapes.size(); i++)
	{
		glGenVertexArrays(1, &m_shape.vao);
		glBindVertexArray(m_shape.vao);

		glGenBuffers(1, &m_shape.vbo);
		glGenBuffers(1, &m_shape.p_normal);
		glGenBuffers(1, &m_shape.vboTex);
		glGenBuffers(1, &m_shape.ebo);
		
		glBindBuffer(GL_ARRAY_BUFFER, m_shape.vbo);
		glBufferData(GL_ARRAY_BUFFER, shapes[i].mesh.positions.size() * sizeof(float), 
			&shapes[i].mesh.positions[0], GL_STATIC_DRAW);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

		glBindBuffer(GL_ARRAY_BUFFER, m_shape.vboTex);
		glBufferData(GL_ARRAY_BUFFER, shapes[i].mesh.texcoords.size() * sizeof(float), shapes[i].mesh.texcoords.data(), GL_STATIC_DRAW);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0);

		glBindBuffer(GL_ARRAY_BUFFER, m_shape.p_normal);
		glBufferData(GL_ARRAY_BUFFER, shapes[i].mesh.normals.size() * sizeof(float), shapes[i].mesh.normals.data(), GL_STATIC_DRAW);
		glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, 0);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_shape.ebo);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, shapes[i].mesh.indices.size() * sizeof(unsigned int), shapes[i].mesh.indices.data(), GL_STATIC_DRAW);
		m_shape.materialId = shapes[i].mesh.material_ids[0];
		m_shape.indexCount = shapes[i].mesh.indices.size();

		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);
		glEnableVertexAttribArray(2);
	}

	texture_data tdata = load_png("assets/myManDiffuse.png");

	glGenTextures( 1, &m_shape.m_texture );
	glBindTexture( GL_TEXTURE_2D, m_shape.m_texture);


	glTexImage2D( GL_TEXTURE_2D, 0, GL_RGBA32F, tdata.width, tdata.height, 0, GL_RGBA, GL_UNSIGNED_BYTE, tdata.data);
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE );
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE );
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
}


void Mesh::bind()
{
	glBindVertexArray(m_shape.vao);
}


void Mesh::attachProgram(ShaderProgram &program)
{
	m_program = &program;
}


