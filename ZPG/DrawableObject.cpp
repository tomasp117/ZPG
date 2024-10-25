#include "DrawableObject.h"

DrawableObject::DrawableObject(const float* points, size_t size, bool hasNormal, GLenum mode, GLint first, GLsizei count, const char* vertex_shader, const char* fragment_shader, Camera* camera)
{
    this->shaderProgram = new ShaderProgram(mode, first, count, camera );
    this->shaderProgram->createShaderProgram(vertex_shader, fragment_shader);
    this->model = new Model();
    this->model->createBuffer(points, size, hasNormal);
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
 
//DrawableObject::DrawableObject(Model* model, ShaderProgram* shader) : model(model), shaderProgram(shader), transformation(&Transformation())
//{
//}

void DrawableObject::render() {
    // Use the shader program
    this->shaderProgram->useProgram();

    this->shaderProgram->SetMatrix(this->getTransformation()->getMatrix());

    //this->shaderProgram->update();

    // Bind the model's VAO
    this->model->bindVAO();

    // Draw the object with the current shader and transformation
    this->shaderProgram->drawShaderArrays();
}