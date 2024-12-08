#pragma once

// PRO0366 Tomáš Prorok 

#include "Rotate.h"

class DynamicRotate : public Rotate 
{
private:
	float speed; // Speed of the rotation
	bool isDynamic; // Is the rotation dynamic

public:
	DynamicRotate(float angle, glm::vec3 axis);

	void dynamicUpdate(float deltaTime) override; // Update the rotation

	// bool getIsDynamic() override; 
	
};

