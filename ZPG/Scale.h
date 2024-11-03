#pragma once
#include "TransformationComponent.h"
class Scale : public TransformationComponent
{
private:
	glm::vec3 scale;

public:
	Scale(glm::vec3 scale);
	glm::mat4 Apply(glm::mat4 matrix) override;
};

