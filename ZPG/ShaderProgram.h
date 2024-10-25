#pragma once
#include <GL/glew.h>
#include <stdio.h>
//Include GLM  
#include <glm/vec3.hpp> // glm::vec3
#include <glm/vec4.hpp> // glm::vec4
#include <glm/mat4x4.hpp> // glm::mat4
#include <glm/gtc/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale, glm::perspective
#include <glm/gtc/type_ptr.hpp> // glm::value_ptr

#include <vector>
#include <iostream>

#include "Observer.h"
#include "Camera.h"

class Camera;

class ShaderProgram : Observer
{
private:
	GLenum mode;
	GLint first;
	GLsizei count;
	GLuint shaderProgram;

	Camera* camera;

public:
	ShaderProgram(GLenum mode, GLint first, GLsizei count, Camera* camera);
	~ShaderProgram();
	void createShaderProgram(const char* vertex_shader, const char* fragment_shader);
	void checkLinking(GLuint shader);
	void checkCompilation(GLuint shader);
	void drawShaderArrays();
	void useProgram();
	//GLuint getShaderProgram() const;
	void setShaderProgram(GLuint program);
	void SetMatrix(glm::mat4 Matrix);
	void SetViewMatrix();
	void SetProjectionMatrix();

	void update() override;
};

