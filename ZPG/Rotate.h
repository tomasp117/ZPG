#pragma once
#include "TransformationComponent.h"
class Rotate : public TransformationComponent
{
private:
	float angle;
	glm::vec3 axis;

public:
	Rotate(float angle, glm::vec3 axis);
	glm::mat4 Apply(glm::mat4 matrix) override;
};

