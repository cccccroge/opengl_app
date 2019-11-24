#include "Texture.h"
#define STB_IMAGE_IMPLEMENTATION
#include "STB/stb_image.h"
#include <iostream>


Texture::Texture(const char *path) : 
    width(0), height(0), data(NULL), type(""), path(path)
{
	std::cout << "constructing Texture: " << std::string(path) << std::endl;

	stbi_set_flip_vertically_on_load(1);

	int BPP;	// byte per pixel?
	data = stbi_load(path, &width, &height, &BPP, 4);
	if (data != NULL) {
		std::cout << "loading pic successfully" << std::endl;
		setUp();
	}
	else {
		std::cout << "failed to load pic" << std::endl;
	}
}


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
	program.setUniform1i(
		(tex_prefix + std::to_string(index)).c_str(), 
		(GLint)index);
}