#pragma once
#include "Rotate.h"

class DynamicRotate : public Rotate
{
private:
	float speed;
	bool isDynamic;

public:
	DynamicRotate(float angle, glm::vec3 axis);
	void dynamicUpdate(float deltaTime) override;

	bool getIsDynamic() override;
	
};

