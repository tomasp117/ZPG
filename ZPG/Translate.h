#pragma once
#include "TransformationComponent.h"
class Translate : public TransformationComponent
{
protected:
	glm::vec3 translate; 
	
public:
	Translate(glm::vec3 translate);
	glm::mat4 apply(glm::mat4 matrix) override;
};

