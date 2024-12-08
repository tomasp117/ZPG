#include "DynamicRotate.h"

DynamicRotate::DynamicRotate(float angle, glm::vec3 axis) : Rotate(angle, axis)
{
	this->angle = angle;
	this->axis = axis;
    this->speed = 30.0f;
    //this->isDynamic = true;
}

void DynamicRotate::dynamicUpdate(float deltaTime)
{        
    this->angle += this->speed*deltaTime;

    //printf("DYNAMIIIIIIC %f\n", deltaTime);
    if (this->angle > 360.0f) this->angle -= 360.0f;
}

//bool DynamicRotate::getIsDynamic()
//{
//	return this->isDynamic;
//}