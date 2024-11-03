#include "Light.h"

Light::Light(glm::vec3 lightPosition, glm::vec3 lightColor, glm::vec3 objectColor, float lightIntensity, float ambientStrength)
{
	this->lightPosition = lightPosition;

	this->lightColor = lightColor;

	this->objectColor = objectColor;

	this->lightIntensity = lightIntensity;

	this->ambientStrength = ambientStrength;
}

glm::vec3 Light::GetLightPosition()
{
	return this->lightPosition;
}

glm::vec3 Light::GetLightColor()
{
	return this->lightColor * lightIntensity;
}

glm::vec3 Light::GetObjectColor()
{
	return this->objectColor;
}

void Light::SetLightPosition(glm::vec3 newPosition)
{
	this->lightPosition = newPosition;

	this->notifyObservers();
}

void Light::SetLightColor(glm::vec3 newColor)
{
	this->lightColor = newColor;

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
		observer->update();
	}
}
