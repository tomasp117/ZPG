#include "Translate.h"

Translate::Translate(glm::vec3 translate)
{
    this->translate = translate;
}

//glm::mat4 Translate::apply(glm::mat4 matrix)
//{
//    return glm::translate(matrix, this->translate);
//}

glm::mat4 Translate::getMatrix()
{
	return glm::translate(glm::mat4(1.0f), this->translate);
}
