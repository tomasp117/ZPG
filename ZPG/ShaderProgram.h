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
#include "Material.h"

using namespace std;

class Camera;

class ShaderProgram : public Observer
{
private:
	GLenum mode;
	GLint first;
	GLsizei count;
	GLuint shaderProgram;
	ShaderLoader* shaderLoader;

	int numLights;


public:
	ShaderProgram(GLenum mode, GLint first, GLsizei count, int numLights);
	~ShaderProgram();
	void createShaderProgram(const char* vertex_shader, const char* fragment_shader);
	void checkLinking(GLuint shader);
	void checkCompilation(GLuint shader);
	void drawShaderArrays();
	void useProgram();
	void disableProgram();
	//GLuint getShaderProgram() const;
	void setShaderProgram(GLuint program);
	void setMatrix(glm::mat4 Matrix);
	void setViewMatrix(Camera* camera);
	void setProjectionMatrix(Camera* camera);
	void setMatrixNormal(glm::mat3 normalMatrix);
	void setCameraViewPos(Camera* camera);

	void setNumberLights(int numLights);

	void setLightUniforms(Light* light);

	void setObjectUniforms(glm::vec3& color);

	void setMaterialUniforms(Material* material);

	void update(Subject* subject) override;

	//void update() override;
};

