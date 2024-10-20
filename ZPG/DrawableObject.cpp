#include "DrawableObject.h"

void DrawableObject::setShader(const ShaderProgram& shader) {
    this->shaderProgram = shader;
}

void DrawableObject::setModel(const Models& newModel) {
    this->model = newModel;
}

void DrawableObject::setTransformation(const Transformation& newTransformation) {
    this->transformation = newTransformation;
}

Transformation DrawableObject::getTransformation() const
{
    return this->transformation;
}
ShaderProgram& DrawableObject::getShader()
{
    return this->shaderProgram;
}
/*
Transformation& DrawableObject::getTransformation()
{
    return this->transformation;
}*/
 
DrawableObject::DrawableObject(Models& model, ShaderProgram& shader) : model(model), shaderProgram(shader), transformation(Transformation())
{
}

void DrawableObject::render() {
    // Use the shader program
    this->shaderProgram.useProgram();

    this->shaderProgram.SetMatrix(transformation.getMatrix());

    // Bind the model's VAO
    this->model.bindVAO();

    // Draw the object with the current shader and transformation
    this->shaderProgram.drawShaderArrays();
}