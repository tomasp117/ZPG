#include "Transformation.h"

Transformation::Transformation() {
    // Initialize with the identity matrix
    modelMatrix = glm::mat4(1.0f);
}

glm::mat4 Transformation::getMatrix() const {
    return modelMatrix;
}

void Transformation::translate(const glm::vec3& translation) {
    // Apply translation to the model matrix
    modelMatrix = glm::translate(modelMatrix, translation);
}

void Transformation::rotate(float angle, const glm::vec3& axis) {
    // Apply rotation to the model matrix
    modelMatrix = glm::rotate(modelMatrix, glm::radians(angle), axis);
}

void Transformation::scale(const glm::vec3& scale) {
    // Apply scaling to the model matrix
    modelMatrix = glm::scale(modelMatrix, scale);
}

