#pragma once
#include "TransformationComponent.h"
class Scale : public TransformationComponent
{
private:
	glm::vec3 scale;

public:
	Scale(glm::vec3 scale);
	//glm::mat4 apply(glm::mat4 matrix) override;
	glm::mat4 getMatrix() override;
};