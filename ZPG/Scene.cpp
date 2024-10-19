#include "Scene.h"

Scene::Scene()
{
    
}

Transformation Scene::getActiveTransformation() {
    if (!objects.empty()) {
        return objects[0].getTransformation();  // Z�sk�n� transformace prvn�ho objektu ve sc�n�
    }
    return Transformation();  // Vr�t� v�choz� (identity) transformaci, pokud nen� ��dn� objekt
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


