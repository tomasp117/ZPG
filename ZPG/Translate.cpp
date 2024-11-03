#include "Translate.h"

Translate::Translate(glm::vec3 translate)
{
    this->translate = translate;
}

glm::mat4 Translate::Apply(glm::mat4 matrix)
{
    return glm::translate(matrix, this->translate);
}
