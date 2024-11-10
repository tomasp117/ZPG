#include "Rotate.h"

Rotate::Rotate(float angle, glm::vec3 axis, bool isDynamic)
{
    this->angle = angle;
    this->axis = axis;
    this->isDynamic = isDynamic;
    isDynamic ? this->speed = 0.5f : this->speed = 0.0f;
}

glm::mat4 Rotate::apply(glm::mat4 matrix)
{
    return glm::rotate(matrix, glm::radians(this->angle), this->axis);
}

void Rotate::dynamicUpdate() {
    
    if (isDynamic) {
        
        
        this->angle += this->speed;

        //printf("DYNAMIIIIIIC %f\n", deltaTime);
        if (this->angle > 360.0f) this->angle -= 360.0f;
    }
}