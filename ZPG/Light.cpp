#include "Light.h"
#include "Camera.h"

Light::Light(int id, glm::vec3 lightPosition, glm::vec3 lightColor, float ambientStrength, glm::vec3 direction, int lightType, float outerCutOff, float cutOff)
{
	this->lightPosition = lightPosition;

	this->lightColor = lightColor;

	this->ambientStrength = ambientStrength;

	this->id = id;

	this->direction = direction;

	this->lightType = lightType;

	this->outerCutOff = outerCutOff;

	this->cutOff = cutOff;
}

int Light::getId()
{
	return this->id;
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

int Light::getLightType()
{
	return this->lightType;
}

glm::vec3 Light::getLightDirection()
{
	return this->direction;
}

float Light::getOuterCutOff()
{
	return this->outerCutOff;
}

float Light::getCutOff()
{
	return this->cutOff;
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

void Light::setLightDirection(glm::vec3 newLightDir)
{
	this->direction = newLightDir;

	this->notifyObservers();
}

void Light::setLightType(int newLightType)
{
	this->lightType = newLightType;

	this->notifyObservers();
}

void Light::setOuterCutOff(float newOuterCutOff)
{
	this->outerCutOff = newOuterCutOff;

	this->notifyObservers();
}

void Light::setCutOff(float newCutOff)
{
	this->cutOff = newCutOff;

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

void Light::update(Subject* subject)
{
	Camera* camera = (Camera*)subject;
	setLightDirection(camera->getTarget());
	setLightPosition(camera->getPosition());

}
