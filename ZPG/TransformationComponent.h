#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class TransformationComponent
{
public:
	virtual glm::mat4 apply(glm::mat4 matrix) = 0;
	virtual void dynamicUpdate() {}
};

