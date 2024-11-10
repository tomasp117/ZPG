#pragma once
#include "TransformationComponent.h"
class Translate : public TransformationComponent
{
private:
	glm::vec3 translate;
	bool isDynamic;
	float speed;  
	

public:
	Translate(glm::vec3 translate);
	glm::mat4 apply(glm::mat4 matrix) override;
};

