#include "Transformation.h"
#include "Rotate.h"
#include "Translate.h"
#include "Scale.h"

#include <iostream>

Transformation::Transformation() {
    // Initialize with the identity matrix
    modelMatrix = glm::mat4(1.0f);
	position = glm::vec3(0.0f);
}

void Transformation::reset()
{
	this->transformations.clear();
	this->modelMatrix = glm::mat4(1.0f);
}

void Transformation::addComponent(TransformationComponent* tranformation)
{
    this->transformations.push_back(tranformation);
    updateModelMatrix();
}

void Transformation::updateModelMatrix() {
    this->modelMatrix = glm::mat4(1.0f);  // Start with the identity matrix

	// Set the position of the object for skybox mainly
	this->modelMatrix[3].x = this->position.x;
	this->modelMatrix[3].y = this->position.y;
	this->modelMatrix[3].z = this->position.z;

    // Apply all transformations in sequence
    for (auto& transformation : this->transformations) {
		this->modelMatrix *= transformation->getMatrix(); // Multiply the current matrix by the transformation matrix to apply it
    }
}

void Transformation::updateDynamicComponents(float deltaTime) {

    for (auto* transformation : this->transformations) {
        //if (transformation->getIsDynamic()) {
            transformation->dynamicUpdate(deltaTime);
       // }
    }
	updateModelMatrix();
}

void Transformation::setPosition(glm::vec3 position)
{
	this->position = position;
    updateModelMatrix();
}

glm::mat4& Transformation::getMatrix() {
    return this->modelMatrix;
}

