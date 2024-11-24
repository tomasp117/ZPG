#include "Model.h"

Model::Model()
{
	this->VAO = 0;
	this->VBO = 0;
}

Model::~Model()
{
	if (this->VBO != 0)
	{
		glDeleteBuffers(1, &this->VBO);
		this->VBO = 0;
	}
	if (this->VAO != 0)
	{
		glDeleteVertexArrays(1, &this->VAO);
		this->VAO = 0;
	}
}

void Model::createBuffer(const float* points, size_t size, bool hasNormal, bool hasTexture)
{
	int stride = 3;
	if (hasNormal)
		stride += 3;
	if (hasTexture)
		stride += 2;
	//Vertex Array Object (VAO)
	glGenVertexArrays(1, &this->VAO); //generate the VAO
	glBindVertexArray(this->VAO); //bind the VAO

	glGenBuffers(1, &this->VBO); // generate the VBO
	glBindBuffer(GL_ARRAY_BUFFER, this->VBO); //bind the VBO

	glBufferData(GL_ARRAY_BUFFER, size, points, GL_STATIC_DRAW); // Load data into VBO
	
	// Enable and define vertex attribute for position
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, stride * sizeof(float), (GLvoid*)0);
	
	if (hasNormal) {
		// Enable and define vertex attribute for normal
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, stride * sizeof(float), (GLvoid*)(3 * sizeof(float)));
	}

	if (hasTexture) {
		// Enable and define vertex attribute for texture
		glEnableVertexAttribArray(2);
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, stride * sizeof(float), (GLvoid*)(6 * sizeof(float)));
	}

	// Unbind VAO and VBO to prevent accidental modification
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	
}

void Model::bindVAO()
{
	glBindVertexArray(this->VAO);
}

void Model::unbindVAO()
{
	glBindVertexArray(0);
}


