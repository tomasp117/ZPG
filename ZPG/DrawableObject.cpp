#include "DrawableObject.h"

DrawableObject::DrawableObject(const float* points, size_t size, bool hasNormal,
    GLenum mode, GLint first, const char* vertex_shader, const char* fragment_shader, Camera* camera, vector<Light*> lights)
{
    GLsizei count = hasNormal == true ? size / sizeof(float) / 6 : size / sizeof(float) / 3;

    // Initialize shader program
    this->shaderProgram = new ShaderProgram(mode, first, count, camera, lights);
    this->shaderProgram->createShaderProgram(vertex_shader, fragment_shader);

    // Initialize model
    this->model = new Model();
    this->model->createBuffer(points, size, hasNormal);

    this->objectColor = glm::vec3(0.0f, 1.0f, 0.0f); // Default green

    this->transformation = new Transformation(); // Initialize transformation
}

DrawableObject::DrawableObject(const float* points, size_t size, bool hasNormal,
    GLenum mode, GLint first, GLsizei count, const char* vertex_shader, const char* fragment_shader, Camera* camera, vector<Light*> lights)
{
    // Initialize shader program
    this->shaderProgram = new ShaderProgram(mode, first, count, camera, lights);
    this->shaderProgram->createShaderProgram(vertex_shader, fragment_shader);

    // Initialize model
    this->model = new Model();
    this->model->createBuffer(points, size, hasNormal);

    this->objectColor = glm::vec3(0.0f, 1.0f, 0.0f); // Default green

    this->transformation = new Transformation(); // Initialize transformation
}

DrawableObject::DrawableObject(Model* model, ShaderProgram *shader)
{
    this->shaderProgram = shader;

    this->model = model;

    this->objectColor = glm::vec3(0.0f, 1.0f, 0.0f); // Default green

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

void DrawableObject::SetColor(glm::vec3 color)
{
    this->objectColor = color;
}


void DrawableObject::render() {
    this->shaderProgram->useProgram();

    this->shaderProgram->SetMatrix(this->getTransformation()->getMatrix()); // Pass the transformation matrix to the shader

    this->shaderProgram->SetObjectUniforms(this->objectColor);

    this->model->bindVAO();

    this->shaderProgram->drawShaderArrays();
}