#pragma once
#include <vector>
#include "DrawableObject.h"
#include "ShaderProgram.h"
#include "Transformation.h"
#include "Camera2.h"

//Include the standard C++ headers  
#include <stdlib.h>
#include <stdio.h>
#include <vector>
class Scene
{
private:
	std::vector<DrawableObject> objects;
    Camera2* camera;

public:
    Scene(Camera2* camera);

    void addObject(const DrawableObject& object);  // Add object to scene
    void setShaderForAllObjects(const ShaderProgram& shader);  // Set a shader for all objects
    void setTransformationForAllObjects(const Transformation& transformation);  // Apply transformation to all objects
    void render();  // Render all objects in the scene
    //std::vector<DrawableObject> getObjects();
    std::vector<DrawableObject>& getObjects();
    Camera2* getCamera();
};

