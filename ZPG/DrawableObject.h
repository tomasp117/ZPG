#pragma once

// PRO0366 Tomáš Prorok 

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
	int id;																    // ID of the object
    ShaderProgram* shaderProgram;                                           // Shader program used to draw the object
    Model* model;                                                           // Model containing the VAO and VBO
    Transformation* transformation;                                         // Transformation (position, rotation, scaling)
    glm::vec3 objectColor;                                                  // Color of the object (default = green)
	Material* material; 													// Material of the object
	Texture* texture; 														// Texture of the object



public:
	// Constructors
	// Yes this could be done with one constructor and functions to set the values, but this is more readable and easier to use
    DrawableObject(Model* model, ShaderProgram* shader);
	DrawableObject(Model* model, ShaderProgram* shader, Material* material);
	DrawableObject(Model* model, ShaderProgram* shader, Material* material, Texture* texture);
	DrawableObject(Model* model, ShaderProgram* shader, Texture* texture);

	virtual void render(); 												// Render the object 

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

