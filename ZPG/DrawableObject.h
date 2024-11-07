#pragma once
#include "Model.h"
#include "Transformation.h"
#include "ShaderProgram.h"
#include "Camera.h"
#include "Light.h"
class DrawableObject
{
private:
    ShaderProgram* shaderProgram;   // Shader program used to draw the object
    Model* model;                  // Model containing the VAO and VBO
    Transformation* transformation; // Transformation (position, rotation, scaling)

public:
    // Konstruktor s parametry (napøíklad pøiøazení modelu a shaderu)
    //DrawableObject(Model* model, ShaderProgram* shader);
    DrawableObject(const float* points, size_t size, bool hasNormal, GLenum mode, GLint first, const char* vertex_shader, const char* fragment_shader, Camera* camera, Light* light);
    DrawableObject(Model* model, ShaderProgram* shader);
    //DrawableObject(Model model, ShaderProgram shader);
    void render(); // Pro vykreslení objektu

    void setShader( ShaderProgram* shader); // Set the shader for the object
    void setModel( Model* newModel);      // Set the model (geometry)
    void setTransformation( Transformation* newTransformation); // Set the transformations
    Transformation* getTransformation();
    void AddComponent(TransformationComponent* transformationComponent);
};

