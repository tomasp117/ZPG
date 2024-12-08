#pragma once

// PRO0366 Tomáš Prorok 

//Include GLEW
#include <GL/glew.h>
//Include GLFW  
#include <GLFW/glfw3.h>  

//Include GLM  
#include <glm/vec3.hpp> // glm::vec3
#include <glm/vec4.hpp> // glm::vec4
#include <glm/mat4x4.hpp> // glm::mat4
#include <glm/gtc/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale, glm::perspective
#include <glm/gtc/type_ptr.hpp> // glm::value_ptr

//Include the standard C++ headers  
#include <stdlib.h>
#include <stdio.h>
#include <vector>

#include "Subject.h"

using namespace std;

class Light : public Subject, public Observer
{
private:	 
    int id;

	glm::vec3 lightPosition; // Position of the light in world coordinates
	glm::vec3 lightColor; // Color of the light
    float ambientStrength; // Ambient lighting strength

	glm::vec3 direction; // Direction of the light
    int lightType; 

	float outerCutOff; // Outer cut off angle for spotlights
	float cutOff; // Cut off angle for spotlights

     vector<Observer*> observers; // List of observers to notify on changes
public:
	Light(int id, glm::vec3 lightPosition, glm::vec3 lightColor, float ambientStrength, glm::vec3 direction, int lightType, float outerCutOff, float cutOff);

    // Getters
	int getId();
    glm::vec3 getLightPosition();
    glm::vec3 getLightColor();
    float getAmbientStrength();
    int getLightType();
    glm::vec3 getLightDirection();
	float getOuterCutOff();
	float getCutOff();

    // Setters
    void setLightPosition(glm::vec3 newPosition);
    void setLightColor(glm::vec3 newColor);
    void setAmbientStrength(float newAmbientStrength);
    void setLightDirection(glm::vec3 newLightDir);
	void setLightType(int newLightType);
	void setOuterCutOff(float newOuterCutOff);
	void setCutOff(float newCutOff);

    // Observer pattern functions to add observers and notify them of changes
    void addObserver(Observer* observer) override;
    void notifyObservers() override;

    void update(Subject* subject) override; 
};

