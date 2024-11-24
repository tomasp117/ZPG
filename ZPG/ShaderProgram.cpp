#include "ShaderProgram.h"
#include <stdlib.h>

ShaderProgram::ShaderProgram(GLenum mode, GLint first, GLsizei count, int numLights)
{
	this->shaderProgram = 0;
	this->mode = mode;
	this->first = first;
	this->count = count;
	
	this->numLights = numLights;
}

ShaderProgram::~ShaderProgram()
{
	if (shaderProgram != 0)
	{
		glDeleteProgram(shaderProgram);
	}
}

void ShaderProgram::createShaderProgram(const char* vertex_shader, const char* fragment_shader)
{
	this->shaderLoader = new ShaderLoader(vertex_shader, fragment_shader, &this->shaderProgram);
	useProgram();
	setNumberLights(numLights);
	disableProgram();
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

void ShaderProgram::checkCompilation(GLuint shader)
{
	GLint status;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
	if (status == GL_FALSE)
	{
		GLint infoLogLength;
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLogLength);
		GLchar* strInfoLog = new GLchar[infoLogLength + 1];
		glGetShaderInfoLog(shader, infoLogLength, NULL, strInfoLog);
		fprintf(stderr, "Shader compilation failure: %s\n", strInfoLog);
		delete[] strInfoLog;
		exit(EXIT_FAILURE);
	}
}

void ShaderProgram::drawShaderArrays()
{
	glDrawArrays(this->mode, this->first, this->count);
}

void ShaderProgram::useProgram()
{
	glUseProgram(this->shaderProgram);
}

void ShaderProgram::disableProgram()
{
	glUseProgram(0);
}
/*
GLuint Shaders::getShaderProgram() const {
	return this->shaderProgram;
}*/


void ShaderProgram::setShaderProgram(GLuint program) {
	this->shaderProgram = program;
}

void ShaderProgram::setMatrix(glm::mat4 Matrix)
{
	GLuint uniform = glGetUniformLocation(this->shaderProgram, "modelMatrix");
	glUniformMatrix4fv(uniform, 1, GL_FALSE, &Matrix[0][0]);
}
void ShaderProgram::setViewMatrix(Camera* camera)
{
	// Získej view matici z kamery

	glm::mat4 viewMatrix = camera->getViewMatrix();
	GLint viewLoc = glGetUniformLocation(this->shaderProgram, "viewMatrix");
	if (viewLoc == -1) {
		//printf("Error: Cannot find uniform 'viewMatrix' in shader!\n");
		return;
	}
	else {
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, &viewMatrix[0][0]);
	}
}
void ShaderProgram::setProjectionMatrix(Camera* camera)
{
	//glm::mat4 projectionMatrix = this->camera->getProjectionMatrix();
	GLint projectionLoc = glGetUniformLocation(this->shaderProgram, "projectionMatrix");
	if (projectionLoc == -1) {
		//printf("Error: Cannot find uniform 'projectionMatrix' in shader!\n");
		return;
	}

	glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, &camera->getProjectionMatrix()[0][0]);
}

void ShaderProgram::setMatrixNormal(glm::mat3 normalMatrix)
{
	GLuint uniform = glGetUniformLocation(this->shaderProgram, "normalMatrix");
	if (uniform == -1) {
		//printf("Error: Cannot find uniform 'normalMatrix' in shader!\n");
		return;
	}
	glUniformMatrix3fv(uniform, 1, GL_FALSE, &normalMatrix[0][0]);
}

void ShaderProgram::setCameraViewPos(Camera* camera)
{
	GLint cameraViewLoc = glGetUniformLocation(this->shaderProgram, "viewPosition");

	if (cameraViewLoc == -1) {
		return;
	}

	glUniform3fv(cameraViewLoc, 1, glm::value_ptr(camera->getPosition()));
}

void ShaderProgram::setNumberLights(int numLights) {
	GLint numLightsLoc = glGetUniformLocation(this->shaderProgram, "numLights");
	if (numLightsLoc != -1) glUniform1i(numLightsLoc, numLights);
}

void ShaderProgram::setLightUniforms(Light* light) {
	int index = light->getId();

	GLint lightPosLoc = glGetUniformLocation(this->shaderProgram, ("lights[" + to_string(index) + "].lightPosition").c_str());
	GLint lightColorLoc = glGetUniformLocation(this->shaderProgram, ("lights[" + to_string(index) + "].lightColor").c_str());
	GLint ambientStrengthLoc = glGetUniformLocation(this->shaderProgram, ("lights[" + to_string(index) + "].ambientStrength").c_str());
	GLint lightDirLoc = glGetUniformLocation(this->shaderProgram, ("lights[" + to_string(index) + "].lightDirection").c_str());
	GLint lightTypeLoc = glGetUniformLocation(this->shaderProgram, ("lights[" + to_string(index) + "].lightType").c_str());
	GLint outCutOffLoc = glGetUniformLocation(this->shaderProgram, ("lights[" + to_string(index) + "].outerCutOff").c_str());
	GLint inCutOffLoc = glGetUniformLocation(this->shaderProgram, ("lights[" + to_string(index) + "].cutOff").c_str());

	if (lightPosLoc != -1) glUniform3fv(lightPosLoc, 1, glm::value_ptr(light->getLightPosition()));
	if (lightColorLoc != -1) glUniform3fv(lightColorLoc, 1, glm::value_ptr(light->getLightColor()));
	if (ambientStrengthLoc != -1) glUniform1f(ambientStrengthLoc, light->getAmbientStrength());
	if (lightDirLoc != -1) glUniform3fv(lightDirLoc, 1, glm::value_ptr(light->getLightDirection()));
	if (lightTypeLoc != -1) glUniform1i(lightTypeLoc, light->getLightType());
	if (outCutOffLoc != -1) glUniform1f(outCutOffLoc, glm::cos(glm::radians(light->getOuterCutOff())));
	if (inCutOffLoc != -1) glUniform1f(inCutOffLoc, glm::cos(glm::radians(light->getCutOff())));

}

void ShaderProgram::setObjectUniforms(glm::vec3& color) {
	GLint objectColorLoc = glGetUniformLocation(this->shaderProgram, "objectColor");
	if (objectColorLoc != -1) {
		glUniform3fv(objectColorLoc, 1, glm::value_ptr(color));
	}
}

void ShaderProgram::setMaterialUniforms(Material* material)
{
	GLint raLoc = glGetUniformLocation(this->shaderProgram, "material.ra");
	GLint rdLoc = glGetUniformLocation(this->shaderProgram, "material.rd");
	GLint rsLoc = glGetUniformLocation(this->shaderProgram, "material.rs");
	GLint shininessLoc = glGetUniformLocation(this->shaderProgram, "material.shininess");
	if (raLoc != -1) glUniform1f(raLoc, material->getAmbient());
	if (rdLoc != -1) glUniform1f(rdLoc, material->getDiffuse());
	if (rsLoc != -1) glUniform1f(rsLoc, material->getSpecular());
	if (shininessLoc != -1) glUniform1f(shininessLoc, material->getShininess());
}

void ShaderProgram::setTextureUnit(GLuint unit)
{
	GLint textureLoc = glGetUniformLocation(this->shaderProgram, "textureUnitID");
	if (textureLoc != -1) glUniform1i(textureLoc, unit);
}

void ShaderProgram::setUseTexture(bool useTexture)
{
	GLint useTextureLoc = glGetUniformLocation(this->shaderProgram, "useTexture");
	if (useTextureLoc != -1) glUniform1i(useTextureLoc, useTexture);
}



void ShaderProgram::update(Subject* subject)
{
	
	useProgram();
	
	//camera
	if (typeid(*subject) == typeid(Camera)) {
		Camera* camera = (Camera*)subject;
		setViewMatrix(camera);
		setProjectionMatrix(camera);
		setCameraViewPos(camera);
	}
	//light
	if (typeid(*subject) == typeid(Light)) { 
		Light* light = (Light*)subject;
		setLightUniforms(light);
	}
	disableProgram();

	
	
	//SetObjectUniforms();
}