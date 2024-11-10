#include "Scene.h"

Scene::Scene(Camera* camera)
{
    this->camera = camera;
}

Transformation* Scene::getActiveTransformation() {
    if (!objects.empty()) {
        return objects[0]->getTransformation();  // Z�sk�n� transformace prvn�ho objektu ve sc�n�
    }
    return new Transformation();  // Vr�t� v�choz� (identity) transformaci, pokud nen� ��dn� objekt
}

void Scene::addObject(DrawableObject* object) {
    // Add an object to the scene
    objects.push_back(object);
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
    // Render all objects in the scene
    for (auto& object : objects) {
        object->updateTransformationDynamic();
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


