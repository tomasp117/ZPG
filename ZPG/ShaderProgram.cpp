#include "ShaderProgram.h"
#include <stdlib.h>

ShaderProgram::ShaderProgram(GLenum mode, GLint first, GLsizei count, Camera* camera)
{
	shaderProgram = 0;
	this->mode = mode;
	this->first = first;
	this->count = count;

	this->camera = camera;
	camera->addObserver(this);
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
	//create and compile shaders
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertex_shader, NULL);
	glCompileShader(vertexShader);
	checkCompilation(vertexShader);

	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragment_shader, NULL);
	glCompileShader(fragmentShader);
	checkCompilation(fragmentShader);

	this->shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, fragmentShader);
	glAttachShader(shaderProgram, vertexShader);
	glLinkProgram(shaderProgram);
	checkLinking(this->shaderProgram);

	// Validace shadera
	glValidateProgram(this->shaderProgram);

	GLint validateStatus;
	glGetProgramiv(this->shaderProgram, GL_VALIDATE_STATUS, &validateStatus);
	if (validateStatus == GL_FALSE) {
		GLint infoLogLength;
		glGetProgramiv(this->shaderProgram, GL_INFO_LOG_LENGTH, &infoLogLength);
		GLchar* strInfoLog = new GLchar[infoLogLength + 1];
		glGetProgramInfoLog(this->shaderProgram, infoLogLength, NULL, strInfoLog);
		fprintf(stderr, "Shader validation failure: %s\n", strInfoLog);
		delete[] strInfoLog;
	}



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
		printf("Error: Cannot find uniform 'viewMatrix' in shader!\n");
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
		printf("Error: Cannot find uniform 'projectionMatrix' in shader!\n");
	}

	glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, &camera->getProjectionMatrix()[0][0]);
}

void ShaderProgram::update()
{
	useProgram();
	SetViewMatrix();
	SetProjectionMatrix();

}