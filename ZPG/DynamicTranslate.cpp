#include "DynamicTranslate.h"

DynamicTranslate::DynamicTranslate(glm::vec3 translate) : Translate(translate)
{
	this->translate = translate;
	this->speed = 0.5f;
	this->isDynamic = true;
}

void DynamicTranslate::dynamicUpdate() {
	this->translate.x += this->speed;
	this->translate.z += this->speed;

}

bool DynamicTranslate::getIsDynamic()
{
	return this->isDynamic;
}

