#pragma once
#include <GL/glew.h>
#include <stdio.h>
class Models
{
private:
	GLuint VAO = 0;
	GLuint VBO = 0;
public:
	void createBuffer(const float* points, size_t size);
	void bindVAO();
};

