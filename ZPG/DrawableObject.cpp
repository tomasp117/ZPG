#include "DrawableObject.h"

//DrawableObject::DrawableObject(const float* points, size_t size, bool hasNormal,
//    GLenum mode, GLint first, const char* vertex_shader, const char* fragment_shader, Camera* camera, vector<Light*> lights)
//{
//    GLsizei count = hasNormal == true ? size / sizeof(float) / 6 : size / sizeof(float) / 3;
//
//    // Initialize shader program
//    this->shaderProgram = new ShaderProgram(mode, first, count, camera, lights);
//    this->shaderProgram->createShaderProgram(vertex_shader, fragment_shader);
//
//    for (Light* light : lights) {
//        light->notifyObservers();
//    }
//
//    // Initialize model
//    this->model = new Model();
//    this->model->createBuffer(points, size, hasNormal);
//
//    this->objectColor = glm::vec3(0.0f, 1.0f, 0.0f); // Default green
//
//    this->transformation = new Transformation(); // Initialize transformation
//}

// make only one constructor from this constructors using optional attributes

//DrawableObject::DrawableObject(Model* model, ShaderProgram* shader, Material* material = nullptr, Texture* texture = nullptr) {
//    this->shaderProgram = shader;
//    this->model = model;
//
//    // Pokud material není pøedán, vytvoøí se výchozí
//    this->material = material ? material : new Material(1.0f, 1.0f, 1.0f, 32.0f);
//
//    this->objectColor = glm::vec3(0.0f, 1.0f, 0.0f); // Defaultní barva
//    this->transformation = new Transformation();
//    this->texture = texture; // Pokud texture není pøedán, zùstane nullptr
//}

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
    this->shaderProgram->useProgram();

    this->shaderProgram->setMatrix(this->getTransformation()->getMatrix()); // Pass the transformation matrix to the shader

	this->shaderProgram->setMaterialUniforms(this->material);

	
	if (this->texture != nullptr) {
		this->texture->bind(texture->getTextureID());
		this->shaderProgram->setTextureUnit(texture->getTextureID());
		this->shaderProgram->setUseTexture(true);
	}
    else {
        this->shaderProgram->setObjectUniforms(this->objectColor);
		this->shaderProgram->setUseTexture(false);
    }

    this->model->bindVAO();

	if (model->getNumIndices() > 0) {
		this->shaderProgram->drawShaderElements();
	}
	else {
		this->shaderProgram->drawShaderArrays();
	}

    if (this->texture) {
        this->texture->unbind();
    }
    
	this->model->unbindVAO();

	this->shaderProgram->disableProgram();
}