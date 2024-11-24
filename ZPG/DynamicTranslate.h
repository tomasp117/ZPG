#pragma once
#include "Translate.h"

class DynamicTranslate : public Translate
{
private:
	//glm::vec3 translate;
	float speed;
	bool isDynamic;

public:
	DynamicTranslate(glm::vec3 translate);
	void dynamicUpdate(float deltaTime) override;

	bool getIsDynamic() override;
};

