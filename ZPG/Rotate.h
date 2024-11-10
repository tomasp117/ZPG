#pragma once
#include "TransformationComponent.h"
class Rotate : public TransformationComponent
{
private:
	float angle;
	glm::vec3 axis;
	float speed;
	bool isDynamic;

public:
	Rotate(float angle, glm::vec3 axis, bool isDynamic);
	glm::mat4 apply(glm::mat4 matrix) override;
	void dynamicUpdate() override;
};

