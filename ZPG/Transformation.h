#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "TransformationComponent.h"
#include <vector>

using namespace std;

class Transformation
{
private:
    glm::mat4 modelMatrix;
    vector<TransformationComponent*> transformations;

    vector<TransformationComponent*> dynamicTransformations;

	glm::vec3 position;

public:
    // Getter for the transformation matrix
    glm::mat4& getMatrix();

    // Transformation functions
    Transformation();
    void reset();
    void addComponent(TransformationComponent* tranformation);
    void updateModelMatrix();
    void updateDynamicComponents(float deltaTime);
    void setPosition(glm::vec3 position);
};

