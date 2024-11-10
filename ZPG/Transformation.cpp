#include "Transformation.h"

Transformation::Transformation() {
    // Initialize with the identity matrix
    modelMatrix = glm::mat4(1.0f);
}

void Transformation::AddComponent(TransformationComponent* tranformation)
{
    this->transformations.push_back(tranformation);
    UpdateModelMatrix();
   // this->modelMatrix = tranformation->Apply(this->modelMatrix);
}

void Transformation::UpdateModelMatrix() {
    this->modelMatrix = glm::mat4(1.0f);  // Start with the identity matrix

    // Apply all transformations in sequence
    for (auto& transformation : this->transformations) {
        this->modelMatrix = transformation->Apply(this->modelMatrix);
    }
}

glm::mat4& Transformation::getMatrix() {
    return modelMatrix;
}
