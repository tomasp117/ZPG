#pragma once
#include "Model.h"
#include "Transformation.h"
#include "ShaderProgram.h"
#include "Camera.h"
#include "Light.h"
#include "Material.h"
#include "Texture.h"


class DrawableObject
{
protected:
    int id;
    ShaderProgram* shaderProgram;                                           // Shader program used to draw the object
    Model* model;                                                           // Model containing the VAO and VBO
    Transformation* transformation;                                         // Transformation (position, rotation, scaling)
    glm::vec3 objectColor;                                                  // Color of the object (default = green)
	Material* material;
	Texture* texture; 



public:
    // Constructors for creating drawable obejcts with new shader and model or with already declared before shader and model
    /*DrawableObject(const float* points, size_t size, bool hasNormal, 
        GLenum mode, GLint first, const char* vertex_shader, const char* fragment_shader, Camera* camera, vector<Light*> lights);*/
    DrawableObject(Model* model, ShaderProgram* shader);
	DrawableObject(Model* model, ShaderProgram* shader, Material* material);
	DrawableObject(Model* model, ShaderProgram* shader, Material* material, Texture* texture);
	DrawableObject(Model* model, ShaderProgram* shader, Texture* texture);
    virtual void render();

    // Getters
    Transformation* getTransformation();
	int getID();

    // Setters
    void setShader( ShaderProgram* shader);  
    void setModel( Model* newModel);
    void setTransformation( Transformation* newTransformation);
	void setID(int id);

    void addComponent(TransformationComponent* transformationComponent);    // Add a new transformation component (position, rotation, scale) to the object


    void updateTransformationDynamic(float deltaTime);

    void setColor(glm::vec3 color);
    
};

