#pragma once
#include <vector>
#include "DrawableObject.h"
#include "ShaderProgram.h"
#include "Transformation.h"
#include "SkyBox.h"
class Scene
{
private:
	std::vector<DrawableObject*> objects;

	SkyBox* skybox;

    Camera* camera;

	vector<Light*> lights;

	glm::vec3 insertPosition;

	DrawableObject* selectedObject;

public:
    Scene(Camera* camera, vector<Light*> lights);
    Transformation* getActiveTransformation();
    void addObject(DrawableObject* object);  // Add object to scene
    void setShaderForAllObjects(ShaderProgram* shader);  // Set a shader for all objects
    void setTransformationForAllObjects(Transformation* transformation);  // Apply transformation to all objects
    void render();  // Render all objects in the scene
    //std::vector<DrawableObject> getObjects();
    std::vector<DrawableObject*> getObjects();
    Camera* getCamera();
    vector<Light*> getLights();
	void setSkyBox(SkyBox* skybox);
    void setInsertPosition(glm::vec3 position);
    void InsertObject(DrawableObject* object);
    void deleteSelectedObject();
	void setSelectedObject(int id); 
};

