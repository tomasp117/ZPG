#include "Scale.h"

Scale::Scale(glm::vec3 scale)
{
    this->scale = scale;
}

glm::mat4 Scale::apply(glm::mat4 matrix)
{
    return glm::scale(matrix, this->scale);
}
