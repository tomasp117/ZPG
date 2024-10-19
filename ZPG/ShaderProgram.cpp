#include "ShaderProgram.h"
#include <stdlib.h>

ShaderProgram::ShaderProgram(GLenum mode, GLint first, GLsizei count)
{
	shaderProgram = 0;
	this->mode = mode;
	this->first = first;
	this->count = count;
}

void ShaderProgram::createShaderProgram(const char* vertex_shader, const char* fragment_shader)
{
	//create and compile shaders
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertex_shader, NULL);
	glCompileShader(vertexShader);

	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragment_shader, NULL);
	glCompileShader(fragmentShader);

	this->shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, fragmentShader);
	glAttachShader(shaderProgram, vertexShader);
	glLinkProgram(shaderProgram);
	checkLinking(this->shaderProgram);

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
	
}

void ShaderProgram::checkLinking(GLuint shader)
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

void ShaderProgram::drawShaderArrays()
{
	glDrawArrays(this->mode, this->first, this->count);
}

void ShaderProgram::useProgram(const glm::mat4& M)
{
	GLuint uniform = glGetUniformLocation(this->shaderProgram, "modelMatrix");
	glUseProgram(this->shaderProgram);
	glUniformMatrix4fv(uniform, 1, GL_FALSE, &M[0][0]);
}
/*
GLuint Shaders::getShaderProgram() const {
	return this->shaderProgram;
}*/


void ShaderProgram::setShaderProgram(GLuint program) {
	this->shaderProgram = program;
}