#include "DynamicRotate.h"

DynamicRotate::DynamicRotate(float angle, glm::vec3 axis) : Rotate(angle, axis)
{
	this->angle = angle;
	this->axis = axis;
    this->speed = 0.5f;
    this->isDynamic = true;
}

void DynamicRotate::dynamicUpdate() 
{        
    this->angle += this->speed;

    //printf("DYNAMIIIIIIC %f\n", deltaTime);
    if (this->angle > 360.0f) this->angle -= 360.0f;
}

bool DynamicRotate::getIsDynamic()
{
	return this->isDynamic;
}