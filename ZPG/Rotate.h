#pragma once

// PRO0366 Tomáš Prorok 


#include "TransformationComponent.h"
class Rotate : public TransformationComponent
{
protected:
	float angle;
	glm::vec3 axis;



public:
	Rotate(float angle, glm::vec3 axis);
	// glm::mat4 apply(glm::mat4 matrix) override;
	glm::mat4 getMatrix();
};

