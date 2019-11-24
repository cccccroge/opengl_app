#include "Texture.h"
#define STB_IMAGE_IMPLEMENTATION
#include "STB/stb_image.h"
#include <iostream>


Texture::Texture(const char *path) : 
    width(0), height(0), data(NULL), type(""), path(path)
{
	int n;
	stbi_uc *_data = stbi_load(path, &width, &height, &n, 4);
	if(_data != NULL)
	{
		data = new unsigned char[width * height * 4 * sizeof(unsigned char)];
		memcpy(data, _data, width * height * 4 * sizeof(unsigned char));
		// vertical-mirror image data
		for (size_t i = 0; i < width; i++)
		{
			for (size_t j = 0; j < height / 2; j++)
			{
				for(size_t k = 0; k < 4; k++) {
					std::swap(data[(j * width + i) * 4 + k], data[((height - j - 1) * width + i) * 4 + k]);
				}
			}
		}
		stbi_image_free(_data);

		setUp();
	}
	else {
		std::cout << "failed to load pics" << std::endl;
	}
}


void Texture::setUp()
{
    glGenTextures(1, &tbo);
    glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, tbo);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA32F, width, height, 0, 
        GL_RGBA, GL_UNSIGNED_BYTE, data);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

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