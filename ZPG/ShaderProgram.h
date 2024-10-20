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
#include "Camera2.h"

class Camera2;

class ShaderProgram
{
private:
	GLenum mode;
	GLint first;
	GLsizei count;
	GLuint shaderProgram;

	std::vector<Observer*> observers;
	glm::mat4 viewMatrix;
	glm::mat4 projectionMatrix;
	glm::mat4 M;


public:
	ShaderProgram(GLenum mode, GLint first, GLsizei count);
	void createShaderProgram(const char* vertex_shader, const char* fragment_shader);
	void checkLinking(GLuint shader);
	void drawShaderArrays();
	/*void useProgram(const glm::mat4& M);*/
	void useProgram();

	//GLuint getShaderProgram() const;
	void setShaderProgram(GLuint program);

	//virtual void update(const glm::mat4& viewMatrix, const glm::mat4& projectionMatrix) override;
	//void attachObserver(Observer* observer);  // Pøidání pozorovatele
	//void notifyObservers();  // Notifikování všech pozorovatelù

	//void setUniform(const std::string& name, float value) const;
 //   void setUniform(const std::string& name, int value) const;
 //   void setUniform(const std::string& name, const glm::mat4& matrix) const;
 //   void setUniform(const std::string& name, const glm::vec3& vec) const;

	void SetMatrix(glm::mat4 Matrix);
	void SetViewMatrix(glm::mat4& viewMatrix);
	void SetProjectionMatrix(glm::mat4& projectionMatrix);
};

