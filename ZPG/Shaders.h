#pragma once
#include <GL/glew.h>
#include <stdio.h>
//Include GLM  
#include <glm/vec3.hpp> // glm::vec3
#include <glm/vec4.hpp> // glm::vec4
#include <glm/mat4x4.hpp> // glm::mat4
#include <glm/gtc/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale, glm::perspective
#include <glm/gtc/type_ptr.hpp> // glm::value_ptr
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
	void useProgram(glm::mat4& M);
	//GLuint getShaderProgram() const;
	void setShaderProgram(GLuint program);
};

