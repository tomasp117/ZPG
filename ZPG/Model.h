#pragma once
#include <GL/glew.h>
#include <stdio.h>
class Model
{
private:
	GLuint VAO;
	GLuint VBO;
public:
	Model();
	~Model();
	void createBuffer(const float* points, size_t size, bool hasNormal, bool hasTexture);
	void bindVAO();
	void unbindVAO();
};

