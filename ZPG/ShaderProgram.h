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
#include <string>

#include "Observer.h"
#include "Camera.h"
#include "ShaderLoader.h"
#include "Light.h"

using namespace std;

class Camera;

class ShaderProgram : Observer
{
private:
	GLenum mode;
	GLint first;
	GLsizei count;
	GLuint shaderProgram;
	ShaderLoader* shaderLoader;
	Camera* camera;
	vector<Light*> lights;

public:
	ShaderProgram(GLenum mode, GLint first, GLsizei count, Camera* camera, vector<Light*> lights);
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
	void SetMatrixNormal(glm::mat3 normalMatrix);
	void SetCameraViewPos();

	void SetLightUniforms();

	void SetObjectUniforms(glm::vec3& color);

	void update() override;
};

