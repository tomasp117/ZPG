#include "ShaderProgram.h"
#include <stdlib.h>

ShaderProgram::ShaderProgram(GLenum mode, GLint first, GLsizei count, Camera* camera, vector<Light*> lights)
{
	this->shaderProgram = 0;
	this->mode = mode;
	this->first = first;
	this->count = count;

	this->camera = camera;
	this->camera->addObserver(this);

	this->lights = lights;
	for (Light* light : lights) {
		light->addObserver(this);
	}
	
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
	////create and compile shaders
	//GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	//glShaderSource(vertexShader, 1, &vertex_shader, NULL);
	//glCompileShader(vertexShader);
	//checkCompilation(vertexShader);

	//GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	//glShaderSource(fragmentShader, 1, &fragment_shader, NULL);
	//glCompileShader(fragmentShader);
	//checkCompilation(fragmentShader);

	//this->shaderProgram = glCreateProgram();
	//glAttachShader(shaderProgram, fragmentShader);
	//glAttachShader(shaderProgram, vertexShader);
	//glLinkProgram(shaderProgram);
	//checkLinking(this->shaderProgram);

	//// Validace shadera
	//glValidateProgram(this->shaderProgram);

	//GLint validateStatus;
	//glGetProgramiv(this->shaderProgram, GL_VALIDATE_STATUS, &validateStatus);
	//if (validateStatus == GL_FALSE) {
	//	GLint infoLogLength;
	//	glGetProgramiv(this->shaderProgram, GL_INFO_LOG_LENGTH, &infoLogLength);
	//	GLchar* strInfoLog = new GLchar[infoLogLength + 1];
	//	glGetProgramInfoLog(this->shaderProgram, infoLogLength, NULL, strInfoLog);
	//	fprintf(stderr, "Shader validation failure: %s\n", strInfoLog);
	//	delete[] strInfoLog;
	//}



	//glDeleteShader(vertexShader);
	//glDeleteShader(fragmentShader);

	//this->shaderProgram = this->shaderLoader->loadShader(vertex_shader, fragment_shader);
	this->shaderLoader = new ShaderLoader(vertex_shader, fragment_shader, &this->shaderProgram);

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
/*
GLuint Shaders::getShaderProgram() const {
	return this->shaderProgram;
}*/


void ShaderProgram::setShaderProgram(GLuint program) {
	this->shaderProgram = program;
}

void ShaderProgram::SetMatrix(glm::mat4 Matrix)
{
	GLuint uniform = glGetUniformLocation(this->shaderProgram, "modelMatrix");
	glUniformMatrix4fv(uniform, 1, GL_FALSE, &Matrix[0][0]);
}
void ShaderProgram::SetViewMatrix()
{
	// Získej view matici z kamery

	glm::mat4 viewMatrix = this->camera->getViewMatrix();
	GLint viewLoc = glGetUniformLocation(this->shaderProgram, "viewMatrix");
	if (viewLoc == -1) {
		//printf("Error: Cannot find uniform 'viewMatrix' in shader!\n");
		return;
	}
	else {
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, &viewMatrix[0][0]);
	}
}
void ShaderProgram::SetProjectionMatrix()
{
	//glm::mat4 projectionMatrix = this->camera->getProjectionMatrix();
	GLint projectionLoc = glGetUniformLocation(this->shaderProgram, "projectionMatrix");
	if (projectionLoc == -1) {
		//printf("Error: Cannot find uniform 'projectionMatrix' in shader!\n");
		return;
	}

	glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, &camera->getProjectionMatrix()[0][0]);
}

void ShaderProgram::SetMatrixNormal(glm::mat3 normalMatrix)
{
	GLuint uniform = glGetUniformLocation(this->shaderProgram, "normalMatrix");
	if (uniform == -1) {
		//printf("Error: Cannot find uniform 'normalMatrix' in shader!\n");
		return;
	}
	glUniformMatrix3fv(uniform, 1, GL_FALSE, &normalMatrix[0][0]);
}

void ShaderProgram::SetCameraViewPos()
{
	GLint cameraViewLoc = glGetUniformLocation(this->shaderProgram, "viewPosition");

	if (cameraViewLoc == -1) {
		return;
	}

	glUniform3fv(cameraViewLoc, 1, glm::value_ptr(camera->getPosition()));
}

void ShaderProgram::SetLightUniforms() {
	GLint numLightsLoc = glGetUniformLocation(this->shaderProgram, "numLights");

	if (numLightsLoc != -1) glUniform1i(numLightsLoc, lights.size());

	for (int i = 0; i < lights.size(); i++) {

		GLint lightPosLoc = glGetUniformLocation(this->shaderProgram, ("lights[" + to_string(i) + "].lightPosition").c_str());
		GLint lightColorLoc = glGetUniformLocation(this->shaderProgram, ("lights[" + to_string(i) + "].lightColor").c_str());
		GLint ambientStrengthLoc = glGetUniformLocation(this->shaderProgram, ("lights[" + to_string(i) + "].ambientStrength").c_str());

		if (lightPosLoc != -1) glUniform3fv(lightPosLoc, 1, glm::value_ptr(lights[i]->GetLightPosition()));
		if (lightColorLoc != -1) glUniform3fv(lightColorLoc, 1, glm::value_ptr(lights[i]->GetLightColor()));
		if (ambientStrengthLoc != -1) glUniform1f(ambientStrengthLoc, lights[i]->GetAmbientStrength());

	}


	/*GLint lightPosLoc = glGetUniformLocation(this->shaderProgram, "lightPosition");
	GLint lightColorLoc = glGetUniformLocation(this->shaderProgram, "lightColor");

	if (lightPosLoc != -1) glUniform3fv(lightPosLoc, 1, glm::value_ptr(light->GetLightPosition()));
	if (lightColorLoc != -1) glUniform3fv(lightColorLoc, 1, glm::value_ptr(light->GetLightColor()));*/

}

void ShaderProgram::SetObjectUniforms(glm::vec3& color) {
	GLint objectColorLoc = glGetUniformLocation(this->shaderProgram, "objectColor");
	if (objectColorLoc != -1) {
		glUniform3fv(objectColorLoc, 1, glm::value_ptr(color));
	}
}

void ShaderProgram::update()
{
	useProgram();
	
	//camera
	SetViewMatrix();
	SetProjectionMatrix();
	SetCameraViewPos();

	//light
	SetLightUniforms();
	//SetObjectUniforms();
}