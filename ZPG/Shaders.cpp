#include "Shaders.h"
#include <stdlib.h>

Shaders::Shaders(GLenum mode, GLint first, GLsizei count)
{
	this->mode = mode;
	this->first = first;
	this->count = count;
}

GLuint Shaders::createShaderProgram(const char* vertex_shader, const char* fragment_shader)
{
	//create and compile shaders
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertex_shader, NULL);
	glCompileShader(vertexShader);

	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragment_shader, NULL);
	glCompileShader(fragmentShader);

	GLuint shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, fragmentShader);
	glAttachShader(shaderProgram, vertexShader);
	glLinkProgram(shaderProgram);

	return shaderProgram;
}

void Shaders::checkLinking(GLuint shader)
{
	GLint status;
	glGetProgramiv(shader, GL_LINK_STATUS, &status);
	if (status == GL_FALSE)
	{
		GLint infoLogLength;
		glGetProgramiv(shader, GL_INFO_LOG_LENGTH, &infoLogLength);
		GLchar* strInfoLog = new GLchar[infoLogLength + 1];
		glGetProgramInfoLog(shader, infoLogLength, NULL, strInfoLog);
		fprintf(stderr, "Linker failure: %s\n", strInfoLog);
		delete[] strInfoLog;
		exit(EXIT_FAILURE);
	}
}

void Shaders::drawShaderArrays()
{
	glDrawArrays(this->mode, this->first, this->count);
}

void Shaders::useProgram()
{
	glUseProgram(this->shaderProgram);
}
/*
GLuint Shaders::getShaderProgram() const {
	return this->shaderProgram;
}*/


void Shaders::setShaderProgram(GLuint program) {
	this->shaderProgram = program;
}