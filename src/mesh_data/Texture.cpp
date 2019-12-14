#include "Texture.h"
#include "STB/stb_image.h"
#include <iostream>


Texture::Texture(const char *path) : 
    width(0), height(0), data(NULL), type(""), path(path)
{
	stbi_set_flip_vertically_on_load(1);

	int channel;
	data = stbi_load(path, &width, &height, &channel, 4);
	if (data != NULL) {
		// std::cout << "loading pic successfully" << std::endl;
		setUp();
	}
	else {
		std::cout << "failed to load pic" << std::endl;
	}
}

Texture::Texture(const int width, const int height) : 
    width(width), height(height), data(NULL), type(""), path(NULL)
{
	setUp();
}

Texture::~Texture()
{
	glDeleteTextures(1, &tbo);

	if (data != NULL) {
		stbi_image_free(data);
		data = NULL;
	}
}


/* Model's textures */
void Texture::setUp()
{
    glGenTextures(1, &tbo);
    //glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, tbo);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, 
		GL_RGBA, GL_UNSIGNED_BYTE, data);

    glBindTexture(GL_TEXTURE_2D, 0);
}


void Texture::bind(ShaderProgram &program, const std::string tex_prefix, 
	const int index)
{
    glActiveTexture(GL_TEXTURE0 + index);
	glBindTexture(GL_TEXTURE_2D, tbo);
	program.bind();
	program.setUniform1i(
		(tex_prefix + std::to_string(index)).c_str(), 
		(GLint)index);
}


void Texture::bind()
{
	glBindTexture(GL_TEXTURE_2D, tbo);
}