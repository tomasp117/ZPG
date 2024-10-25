#include "Model.h"

Model::Model() : VAO(0), VBO(0)
{
}

Model::~Model()
{
	if (VBO != 0)
	{
		glDeleteBuffers(1, &VBO);
		VBO = 0; 
	}
	if (VAO != 0)
	{
		glDeleteVertexArrays(1, &VAO);
		VAO = 0;
	}
}

void Model::createBuffer(const float* points, size_t size, bool hasNormal)
{
	//Vertex Array Object (VAO)
	glGenVertexArrays(1, &this->VAO); //generate the VAO
	glBindVertexArray(this->VAO); //bind the VAO

	glGenBuffers(1, &this->VBO); // generate the VBO
	glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
	//glBufferData(GL_ARRAY_BUFFER, sizeof(points2), points2, GL_STATIC_DRAW); // rectangle
	glBufferData(GL_ARRAY_BUFFER, size, points, GL_STATIC_DRAW);
	
	glEnableVertexAttribArray(0); //enable vertex attributes
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (GLvoid*)0);
	
	if (hasNormal) {
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (GLvoid*)(3 * sizeof(float)));
	}

	// Unbind VAO and VBO to prevent accidental modification
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	
}

void Model::bindVAO()
{
	glBindVertexArray(this->VAO);
}


