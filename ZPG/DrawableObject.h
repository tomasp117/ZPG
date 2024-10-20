#pragma once
#include "Models.h"
#include "Transformation.h"
#include "ShaderProgram.h"
class DrawableObject
{
private:
    ShaderProgram shaderProgram;   // Shader program used to draw the object
    Models model;                  // Model containing the VAO and VBO
    Transformation transformation; // Transformation (position, rotation, scaling)

public:
    // Konstruktor s parametry (napøíklad pøiøazení modelu a shaderu)
    DrawableObject(Models& model, ShaderProgram& shader);

    //DrawableObject(Models model, ShaderProgram shader);
    void render(); // Pro vykreslení objektu

    void setShader(const ShaderProgram& shader); // Set the shader for the object
    void setModel(const Models& newModel);      // Set the model (geometry)
    void setTransformation(const Transformation& newTransformation); // Set the transformations
    Transformation getTransformation() const;
    ShaderProgram& getShader();
};

