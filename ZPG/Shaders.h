#pragma once
#include <GL/glew.h>
#include <stdio.h>
class Shaders
{
private:
	GLenum mode;
	GLint first;
	GLsizei count;
	GLuint shaderProgram;

public:
	Shaders(GLenum mode, GLint first, GLsizei count);
	GLuint createShaderProgram(const char* vertex_shader, const char* fragment_shader);
	void checkLinking(GLuint shader);
	void drawShaderArrays();
	void useProgram();
	//GLuint getShaderProgram() const;
	void setShaderProgram(GLuint program);
};

