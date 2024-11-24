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
	this->dynamicTransformations.clear();
	this->modelMatrix = glm::mat4(1.0f);
}

void Transformation::addComponent(TransformationComponent* tranformation)
{
    this->transformations.push_back(tranformation);
	/*if (tranformation->getIsDynamic()) {
		this->dynamicTransformations.push_back(tranformation);
	}*/
    updateModelMatrix();
   // this->modelMatrix = tranformation->Apply(this->modelMatrix);
}

void Transformation::updateModelMatrix() {
    this->modelMatrix = glm::mat4(1.0f);  // Start with the identity matrix
	this->modelMatrix[3].x = this->position.x;
	this->modelMatrix[3].y = this->position.y;
	this->modelMatrix[3].z = this->position.z;

    // Apply all transformations in sequence
    for (auto& transformation : this->transformations) {
        this->modelMatrix = transformation->apply(this->modelMatrix);
    }
}

void Transformation::updateDynamicComponents(float deltaTime) {

    for (auto* transformation : this->transformations) {
        if (transformation->getIsDynamic()) {
            transformation->dynamicUpdate(deltaTime);
        }
    }
	updateModelMatrix();
	/*if (this->dynamicTransformations.empty()) return;
    for (auto& transformation : this->dynamicTransformations) {
        transformation->dynamicUpdate();       
    }
    updateModelMatrix();*/
}

void Transformation::setPosition(glm::vec3 position)
{
	this->position = position;
    updateModelMatrix();
}

glm::mat4& Transformation::getMatrix() {
    return this->modelMatrix;
}

