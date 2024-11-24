#include "Texture.h"


Texture::Texture(const char* filePath)
{
	this->textureID = SOIL_load_OGL_texture(filePath, SOIL_LOAD_RGBA, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
	if (this->textureID == 0)
	{
		printf("Error loading texture: %s\n", filePath);
		exit(EXIT_FAILURE);
	}

	// make the texture reapet itself in both directions and not stretch
	glBindTexture(GL_TEXTURE_2D, this->textureID);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
	// set the texture filtering methods for magnification and minification
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	// unbind the texture
	glBindTexture(GL_TEXTURE_2D, 0);

	
}

Texture::Texture(const char* x_pos, const char* x_neg, const char* y_pos, const char* y_neg, const char* z_pos, const char* z_neg)
{
	// Naètení cubemapy pomocí SOIL
	this->textureID = SOIL_load_OGL_cubemap(
		x_pos, x_neg, y_pos, y_neg, z_pos, z_neg,
		SOIL_LOAD_RGB, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS
	);

	if (this->textureID == 0) {
		printf("Error loading cubemap texture\n");
		exit(EXIT_FAILURE);
	}

	// Vázání cubemap textury
	glBindTexture(GL_TEXTURE_CUBE_MAP, this->textureID);

	// Parametry textury
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	// Odvázání textury
	glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
}

Texture::~Texture()
{
	glDeleteTextures(1, &this->textureID);
}

GLuint Texture::getTextureID()
{
	return this->textureID;
}

void Texture::bind(GLuint unit) const
{
	glActiveTexture(GL_TEXTURE0 + unit);
	glBindTexture(GL_TEXTURE_2D, this->textureID);
}

void Texture::unbind() const
{
	glBindTexture(GL_TEXTURE_2D, 0);
}


void Texture::bindCube(GLuint unit) const
{
	glActiveTexture(GL_TEXTURE0 + unit);
	glBindTexture(GL_TEXTURE_CUBE_MAP, this->textureID);
}

void Texture::unbindCube() const
{
	glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
}