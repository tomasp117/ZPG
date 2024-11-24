#include "DynamicTranslate.h"

DynamicTranslate::DynamicTranslate(glm::vec3 translate) : Translate(translate)
{
	this->translate = translate;
	this->speed = 5.0f;
	this->isDynamic = true;
}

void DynamicTranslate::dynamicUpdate(float deltaTime) {
	this->translate.x += this->speed*deltaTime;
	this->translate.z += this->speed* deltaTime;

	this->translate = glm::vec3(this->translate.x, 0.0f, this->translate.z);
	printf("pos %f %f\n", this->translate.x, this->translate.z);

}

bool DynamicTranslate::getIsDynamic()
{
	return this->isDynamic;
}

