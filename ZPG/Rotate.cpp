#include "Rotate.h"

Rotate::Rotate(float angle, glm::vec3 axis)
{
    this->angle = angle;
    this->axis = axis;
}

glm::mat4 Rotate::Apply(glm::mat4 matrix)
{
    return glm::rotate(matrix, glm::radians(this->angle), this->axis);
}
