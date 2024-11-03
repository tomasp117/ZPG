#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class TransformationComponent
{
public:
	virtual glm::mat4 Apply(glm::mat4 matrix) = 0;
};

