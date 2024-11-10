#include "Light.h"

Light::Light(glm::vec3 lightPosition, glm::vec3 lightColor, float ambientStrength)
{
	this->lightPosition = lightPosition;

	this->lightColor = lightColor;

	this->ambientStrength = ambientStrength;
}

glm::vec3 Light::getLightPosition()
{
	return this->lightPosition;
}

glm::vec3 Light::getLightColor()
{
	return this->lightColor;
}

float Light::getAmbientStrength()
{
	return this->ambientStrength;
}

void Light::setLightPosition(glm::vec3 newPosition)
{
	this->lightPosition = newPosition;

	this->notifyObservers();
}

void Light::setLightColor(glm::vec3 newColor)
{
	this->lightColor = newColor;

	this->notifyObservers();
}

void Light::setAmbientStrength(float newAmbientStrength)
{
	this->ambientStrength = newAmbientStrength;

	this->notifyObservers();
}

void Light::addObserver(Observer* observer)
{
	this->observers.push_back(observer);
}

void Light::notifyObservers()
{
	for (auto observer : this->observers)
	{
		observer->update(this);
	}
}
