#include "DrawableObject.h"

DrawableObject::DrawableObject(const float* points, size_t size, bool hasNormal, GLenum mode, GLint first, const char* vertex_shader, const char* fragment_shader, Camera* camera, Light* light)
{
    GLsizei count = hasNormal == true ? size / sizeof(float) / 6 : size / sizeof(float) / 3;
    this->shaderProgram = new ShaderProgram(mode, first, count, camera, light);
    this->shaderProgram->createShaderProgram(vertex_shader, fragment_shader);
    this->model = new Model();
    this->model->createBuffer(points, size, hasNormal);

    this->transformation = new Transformation();
}

DrawableObject::DrawableObject(Model* model, ShaderProgram *shader)
{
    this->shaderProgram = shader;
    this->model = model;

    this->transformation = new Transformation();
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

Transformation* DrawableObject::getTransformation()
{
    return this->transformation;
}

void DrawableObject::AddComponent(TransformationComponent* transformationComponent) {
    this->transformation->AddComponent(transformationComponent);
}
 
//DrawableObject::DrawableObject(Model* model, ShaderProgram* shader) : model(model), shaderProgram(shader), transformation(&Transformation())
//{
//}

void DrawableObject::render() {
    // Use the shader program
    this->shaderProgram->useProgram();

    this->shaderProgram->SetMatrix(this->getTransformation()->getMatrix());
    this->shaderProgram->SetMatrixNormal(glm::transpose(glm::inverse(glm::mat3(this->getTransformation()->getMatrix()))));
    //this->shaderProgram->update();

    // Bind the model's VAO
    this->model->bindVAO();

    // Draw the object with the current shader and transformation
    this->shaderProgram->drawShaderArrays();
}