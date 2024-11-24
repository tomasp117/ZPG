#pragma once
#include "Observer.h"
#include "DrawableObject.h"

class SkyBox : public DrawableObject, public Observer
{
private:
	//Model* model;
	//ShaderProgram* shader;
	//Texture* texture;
	//Camera* camera;

	glm::vec3 translate;

public:

	SkyBox(Model* model, ShaderProgram* shaderProgram, Texture* texture);

	void render() override;

	void update(Subject* subject) override;
};

