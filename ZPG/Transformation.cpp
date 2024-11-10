#include "Transformation.h"

Transformation::Transformation() {
    // Initialize with the identity matrix
    modelMatrix = glm::mat4(1.0f);
}

void Transformation::addComponent(TransformationComponent* tranformation)
{
    this->transformations.push_back(tranformation);
    updateModelMatrix();
   // this->modelMatrix = tranformation->Apply(this->modelMatrix);
}

void Transformation::updateModelMatrix() {
    this->modelMatrix = glm::mat4(1.0f);  // Start with the identity matrix

    // Apply all transformations in sequence
    for (auto& transformation : this->transformations) {
        this->modelMatrix = transformation->apply(this->modelMatrix);
    }
}

void Transformation::updateDynamicComponents() {
    for (auto& transformation : transformations) {
        transformation->dynamicUpdate();       
    }
    updateModelMatrix();
}

glm::mat4& Transformation::getMatrix() {
    return modelMatrix;
}
