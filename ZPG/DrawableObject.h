#pragma once
#include "Model.h"
#include "Transformation.h"
#include "ShaderProgram.h"
#include "Camera.h"
#include "Light.h"
class DrawableObject
{
private:
    ShaderProgram* shaderProgram;                                           // Shader program used to draw the object
    Model* model;                                                           // Model containing the VAO and VBO
    Transformation* transformation;                                         // Transformation (position, rotation, scaling)
    glm::vec3 objectColor;                                                  // Color of the object (default = green)

public:
    // Constructors for creating drawable obejcts with new shader and model or with already declared before shader and model
    DrawableObject(const float* points, size_t size, bool hasNormal, 
        GLenum mode, GLint first, const char* vertex_shader, const char* fragment_shader, Camera* camera, vector<Light*> lights);
    DrawableObject(const float* points, size_t size, bool hasNormal,
        GLenum mode, GLint first, GLsizei count, const char* vertex_shader, const char* fragment_shader, Camera* camera, vector<Light*> lights);
    DrawableObject(Model* model, ShaderProgram* shader);

    void render();                                                  

    // Getters
    Transformation* getTransformation();

    // Setters
    void setShader( ShaderProgram* shader);  
    void setModel( Model* newModel);
    void setTransformation( Transformation* newTransformation);

    void addComponent(TransformationComponent* transformationComponent);    // Add a new transformation component (position, rotation, scale) to the object


    void updateTransformationDynamic();

    void setColor(glm::vec3 color);
    
};

