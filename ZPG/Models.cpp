#include "Models.h"

void Models::createBuffer(const float* points, size_t size)
{
	
	glGenBuffers(1, &this->VBO); // generate the VBO
	glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
	//glBufferData(GL_ARRAY_BUFFER, sizeof(points2), points2, GL_STATIC_DRAW); // rectangle
	glBufferData(GL_ARRAY_BUFFER, size, points, GL_STATIC_DRAW);
	//Vertex Array Object (VAO)

	glGenVertexArrays(1, &this->VAO); //generate the VAO
	glBindVertexArray(this->VAO); //bind the VAO
	glEnableVertexAttribArray(0); //enable vertex attributes
	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
	//glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (GLvoid*)0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (GLvoid*)(3 * sizeof(float)));
	
}

void Models::bindVAO()
{
	glBindVertexArray(this->VAO);
}


