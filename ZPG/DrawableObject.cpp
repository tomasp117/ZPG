#include "DrawableObject.h"

DrawableObject::DrawableObject(Model* model, ShaderProgram *shader)
{
    this->shaderProgram = shader;
    this->model = model;
	this->material = new Material(1.0f, 1.0f, 1.0f, 32.0f); // Default
    this->objectColor = glm::vec3(0.0f, 1.0f, 0.0f); // Default green
    this->transformation = new Transformation();
	this->texture = nullptr;
}

DrawableObject::DrawableObject(Model* model, ShaderProgram* shader, Material* material)
{
	this->shaderProgram = shader;
	this->model = model;
	this->material = material;
    this->objectColor = glm::vec3(0.0f, 1.0f, 0.0f); // Default
    this->transformation = new Transformation();
	this->texture = nullptr;
}

DrawableObject::DrawableObject(Model* model, ShaderProgram* shader, Material* material, Texture* texture)
{
    this->shaderProgram = shader;
    this->model = model;
    this->material = material;
    this->objectColor = glm::vec3(0.0f, 1.0f, 0.0f); // Default
    this->transformation = new Transformation();
	this->texture = texture;
}

DrawableObject::DrawableObject(Model* model, ShaderProgram* shader, Texture* texture)
{
    this->shaderProgram = shader;
    this->model = model;
	this->material = new Material(1.0f, 1.0f, 1.0f, 32.0f); // Default
    this->objectColor = glm::vec3(0.0f, 1.0f, 0.0f); // Default
    this->transformation = new Transformation();
    this->texture = texture;
}

void DrawableObject::setShader(ShaderProgram* shader) {
    this->shaderProgram = shader;
}

void DrawableObject::setModel(Model* newModel) {
    this->model = newModel;
}

void DrawableObject::setTransformation(Transformation* newTransformation) {
    this->transformation = newTransformation;
}

void DrawableObject::setID(int id)
{
	this->id = id;
}

Transformation* DrawableObject::getTransformation()
{
    return this->transformation;
}

int DrawableObject::getID()
{
	return this->id;
}

void DrawableObject::addComponent(TransformationComponent* transformationComponent) {
    this->transformation->addComponent(transformationComponent);
}

void DrawableObject::updateTransformationDynamic(float deltaTime) {
    this->transformation->updateDynamicComponents(deltaTime);

}

void DrawableObject::setColor(glm::vec3 color)
{
    this->objectColor = color;
}

void DrawableObject::render() {
	this->shaderProgram->useProgram(); // Use the shader program

    this->shaderProgram->setMatrix(this->getTransformation()->getMatrix()); // Pass the transformation matrix to the shader

	this->shaderProgram->setMaterialUniforms(this->material); // Pass the material to the shader

	// If the object has a texture, bind it and pass the texture
	if (this->texture != nullptr) {
		this->texture->bind(texture->getTextureID()); // Bind the texture
		this->shaderProgram->setTextureUnit(texture->getTextureID()); // Pass the texture unit to the shader
		this->shaderProgram->setUseTexture(true);
	}
    else {
		this->shaderProgram->setObjectUniforms(this->objectColor); // Pass the object color to the shader
		this->shaderProgram->setUseTexture(false); 
    }

	this->model->bindVAO();

	if (model->getNumIndices() > 0) {
		this->shaderProgram->drawShaderElements(); // Draw the object .obj
	}
	else {
		this->shaderProgram->drawShaderArrays(); // Draw non .obj objects
	}

	// Unbind the texture and the VAO
    if (this->texture) {
        this->texture->unbind(); 
    }
    
	this->model->unbindVAO();

	this->shaderProgram->disableProgram();
}