#include "Rotate.h"

Rotate::Rotate(float angle, glm::vec3 axis)
{
    this->angle = angle;
    this->axis = axis;
    /*this->isDynamic = isDynamic;
    isDynamic ? this->speed = 0.5f : this->speed = 0.0f;*/
}

//glm::mat4 Rotate::apply(glm::mat4 matrix)
//{
//    return glm::rotate(matrix, glm::radians(this->angle), this->axis);
//}

glm::mat4 Rotate::getMatrix()
{
	return glm::rotate(glm::mat4(1.0f), glm::radians(this->angle), this->axis);
}

