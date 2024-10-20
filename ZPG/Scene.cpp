#include "Scene.h"

Scene::Scene(Camera2* camera) 
{
    this->camera = camera;
}

void Scene::addObject(const DrawableObject& object) {
    // Add an object to the scene
    objects.push_back(object);
}

void Scene::setShaderForAllObjects(const ShaderProgram& shader) {
    // Set the same shader program for all objects in the scene
    for (auto& object : objects) {
        object.setShader(shader);
    }
}

void Scene::setTransformationForAllObjects(const Transformation& transformation) {
    // Set the same transformation for all objects in the scene
    for (auto& object : objects) {
        object.setTransformation(transformation);
    }
}

void Scene::render() {
    // Render all objects in the scene
    for (auto& object : objects) {
        object.render();  // Calls the object's render function
    }
}

std::vector<DrawableObject>& Scene::getObjects()
{
    return this->objects;
}

Camera2* Scene::getCamera()
{
    return this->camera;
}


