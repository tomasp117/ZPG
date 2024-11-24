#include "SkyBox.h"

#include "Translate.h"

SkyBox::SkyBox(Model* model, ShaderProgram* shaderProgram, Texture* texture)
    : DrawableObject(model, shaderProgram, material, texture) {
	//addComponent(new Translate(glm::vec3(0.0f, 0.0f, 0.0f)));
}

void SkyBox::render()
{

	glDisable(GL_DEPTH_TEST);

	this->shaderProgram->useProgram();

	shaderProgram->setMatrix(this->getTransformation()->getMatrix()); // Pass the transformation matrix to the shader
	this->shaderProgram->setMaterialUniforms(this->material);


	if (this->texture != nullptr) {
		this->texture->bindCube(texture->getTextureID());
		this->shaderProgram->setTextureUnit(texture->getTextureID());
		this->shaderProgram->setUseTexture(true);
	}
	else {
		this->shaderProgram->setObjectUniforms(objectColor);
		this->shaderProgram->setUseTexture(false);
	}

	this->model->bindVAO();

	this->shaderProgram->drawShaderArrays();

	if (this->texture) {
		this->texture->unbind();
	}

	this->model->unbindVAO();

	this->shaderProgram->disableProgram();

	if (this->texture != nullptr) {
		this->texture->unbindCube();
	}


	glEnable(GL_DEPTH_TEST);
}

void SkyBox::update(Subject* subject)
{
	if (typeid(*subject) == typeid(Camera)) {
		Camera* camera = (Camera*)subject;

		this->getTransformation()->setPosition(camera->getPosition());
	}
}



