#pragma once

// PRO0366 Tomáš Prorok 


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

	bool followCamera = true;

public:

	SkyBox(Model* model, ShaderProgram* shaderProgram, Texture* texture);

	void render() override;

	void update(Subject* subject) override;

	void setFollowCamera(bool follow);
	bool getFollowCamera();
};

