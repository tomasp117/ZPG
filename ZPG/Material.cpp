#include "Material.h"

Material::Material(float ra, float rd, float rs, float shininess)
{
	this->ra = ra;
	this->rd = rd;
	this->rs = rs;
	this->shininess = shininess;
}

float Material::getAmbient()
{
	return this->ra;
}

float Material::getDiffuse()
{
	return this->rd;
}

float Material::getSpecular()
{
	return this->rs;
}

float Material::getShininess()
{
	return this->shininess;
}

void Material::setAmbient(float ra)
{
	this->ra = ra;
}

void Material::setDiffuse(float rd)
{
	this->rd = rd;
}

void Material::setSpecular(float rs)
{
	this->rs = rs;
}

void Material::setShininess(float shininess)
{
	this->shininess = shininess;
}
