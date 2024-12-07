#include "Scene.h"

Scene::Scene(Camera* camera, vector<Light*> lights)
{
    this->camera = camera;
	this->lights = lights;
	this->selectedObject = nullptr;
}

Transformation* Scene::getActiveTransformation() {
    if (!objects.empty()) {
        return objects[0]->getTransformation();  // Získání transformace prvního objektu ve scénì
    }
    return new Transformation();  // Vrátí výchozí (identity) transformaci, pokud není žádný objekt
}

void Scene::addObject(DrawableObject* object) {
    // Add an object to the scene
    objects.push_back(object);
	object->setID(objects.size());  // Set the object's ID to its index in the vector
}

void Scene::setShaderForAllObjects(ShaderProgram* shader) {
    // Set the same shader program for all objects in the scene
    for (auto& object : objects) {
        object->setShader(shader);
    }
}

void Scene::setTransformationForAllObjects(Transformation* transformation) {
    // Set the same transformation for all objects in the scene
    for (auto& object : objects) {
        object->setTransformation(transformation);
    }
}

void Scene::render() {
    
	if (objects.empty()) return;
    float deltaTime = 0.016f;

    glEnable(GL_STENCIL_TEST);
    glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);

    if (skybox != nullptr) {
        glStencilFunc(GL_ALWAYS, skybox->getID(), 0xFF);
        skybox->render();
    }

    // Clear the depth buffer to ensure the SkyBox doesn't interfere with objects
    // glClear(GL_DEPTH_BUFFER_BIT);


    // Render all objects in the scene
    for (auto& object : objects) {
        glStencilFunc(GL_ALWAYS, object->getID(), 0xFF);
        object->updateTransformationDynamic(deltaTime);
        object->render();  // Calls the object's render function       
    }
}

std::vector<DrawableObject*> Scene::getObjects()
{
    return this->objects;
}


Camera* Scene::getCamera()
{
    return this->camera;
}

vector<Light*> Scene::getLights()
{
	return this->lights;
}

void Scene::setSkyBox(SkyBox* skybox)
{
	this->skybox = skybox;
	this->skybox->setID(0);  // Set the skybox's ID to 0
}

void Scene::setInsertPosition(glm::vec3 position)
{
	this->insertPosition = position;
}

void Scene::InsertObject(DrawableObject* object)
{
	if (this->insertPosition == glm::vec3(0.0f))
	{
        return;
	}
	object->getTransformation()->setPosition(this->insertPosition);
	this->addObject(object);
    object->setID(this->objects.size());

	this->camera->notifyObservers();
	for (Light* light : lights) {
		light->notifyObservers();
	}
}

void Scene::deleteSelectedObject()
{
    
	if (this->selectedObject != nullptr) {
        if (this->selectedObject == this->skybox) {
            this->skybox = nullptr;
            return;
        }
		objects.erase(std::remove(objects.begin(), objects.end(), this->selectedObject), objects.end());
		this->selectedObject = nullptr;
	}
}

void Scene::setSelectedObject(int id)
{
	if (this->skybox && this->skybox->getID() == id) {
		this->selectedObject = this->skybox;
		return;
	}
	for (auto& object : objects) {
 
		if (object->getID() == id) {
			this->selectedObject = object;
            break;
		}
		else {
			this->selectedObject = nullptr;
		}
	}
    if (this->selectedObject != nullptr)
    {
        printf("Selected object ID: %d\n", this->selectedObject->getID());
    }

    
}
