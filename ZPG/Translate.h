#pragma once
#include "TransformationComponent.h"
class Translate : public TransformationComponent
{
private:
	glm::vec3 translate;

public:
	Translate(glm::vec3 translate);
	glm::mat4 Apply(glm::mat4 matrix) override;
};

