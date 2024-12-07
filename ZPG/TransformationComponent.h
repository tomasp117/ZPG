#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class TransformationComponent
{
public:
	//virtual glm::mat4 apply(glm::mat4 matrix) {};
	virtual glm::mat4 getMatrix() = 0;

	virtual void dynamicUpdate(float deltaTime) {};
	virtual bool getIsDynamic() { return false; };
};


