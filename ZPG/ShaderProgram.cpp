#include "ShaderProgram.h"
#include <stdlib.h>

ShaderProgram::ShaderProgram(GLenum mode, GLint first, GLsizei count, Camera2* camera)
{
	shaderProgram = 0;
	this->mode = mode;
	this->first = first;
	this->count = count;

	this->camera = camera;
	camera->addShader(this);
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

//void ShaderProgram::useProgram(const glm::mat4& M)
//{
//	GLuint uniform = glGetUniformLocation(this->shaderProgram, "modelMatrix");
//	glUseProgram(this->shaderProgram);
//	setUniform("modelMatrix", M);
//	glUniformMatrix4fv(uniform, 1, GL_FALSE, &M[0][0]);
//}

void ShaderProgram::useProgram()
{
	GLuint uniform = glGetUniformLocation(this->shaderProgram, "modelMatrix");
	glUseProgram(this->shaderProgram);
	//setUniform("modelMatrix", M);
	glUniformMatrix4fv(uniform, 1, GL_FALSE, &M[0][0]);
}

/*
GLuint Shaders::getShaderProgram() const {
	return this->shaderProgram;
}*/


void ShaderProgram::setShaderProgram(GLuint program) {
	this->shaderProgram = program;
}

//void ShaderProgram::update(const glm::mat4& viewMatrix, const glm::mat4& projectionMatrix)
//{
//	GLuint viewLoc = glGetUniformLocation(shaderProgram, "viewMatrix");
//	GLuint projLoc = glGetUniformLocation(shaderProgram, "projectionMatrix");
//
//	// Aktivace shader programu
//	glUseProgram(shaderProgram);
//
//	// Nastavení nových matic
//	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(viewMatrix));
//	glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projectionMatrix));
//}

//// Nastavení uniform pro float
//void ShaderProgram::setUniform(const std::string& name, float value) const {
//	GLuint location = glGetUniformLocation(shaderProgram, name.c_str());
//	if (location != -1) {
//		glUniform1f(location, value);
//	}
//}
//
//// Nastavení uniform pro int
//void ShaderProgram::setUniform(const std::string& name, int value) const {
//	GLuint location = glGetUniformLocation(shaderProgram, name.c_str());
//	if (location != -1) {
//		glUniform1i(location, value);
//	}
//}
//
//// Nastavení uniform pro glm::mat4
//void ShaderProgram::setUniform(const std::string& name, const glm::mat4& matrix) const {
//	GLuint location = glGetUniformLocation(shaderProgram, name.c_str());
//	if (location != -1) {
//		glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
//	}
//}
//
//// Nastavení uniform pro glm::vec3
//void ShaderProgram::setUniform(const std::string& name, const glm::vec3& vec) const {
//	GLuint location = glGetUniformLocation(shaderProgram, name.c_str());
//	if (location != -1) {
//		glUniform3fv(location, 1, glm::value_ptr(vec));
//	}
//}

void ShaderProgram::SetMatrix(glm::mat4 Matrix)
{
	this->M = Matrix;
}

void ShaderProgram::SetViewMatrix(const glm::mat4& viewMatrix)
{
	//glm::mat4 viewMatrix = this->camera->getViewMatrix();
	this->viewMatrix = viewMatrix;
	GLint viewLoc = glGetUniformLocation(this->shaderProgram, "viewMatrix");
	if (viewLoc == -1) {
		printf("Error: Cannot find uniform 'viewMatrix' in shader!\n");
	}
	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, &viewMatrix[0][0]);
}

void ShaderProgram::SetProjectionMatrix(const glm::mat4& projectionMatrix)
{
	//glm::mat4 projectionMatrix = this->camera->getProjectionMatrix();
	this->projectionMatrix = projectionMatrix;
	GLint projectionLoc = glGetUniformLocation(this->shaderProgram, "projectionMatrix");
	if (projectionLoc == -1) {
		printf("Error: Cannot find uniform 'projectionMatrix' in shader!\n");
	}

	glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, &projectionMatrix[0][0]);
}

void ShaderProgram::update()
{
	useProgram();  // Activate the shader program
	SetViewMatrix(camera->getViewMatrix());
	SetProjectionMatrix(camera->getProjectionMatrix());

}


