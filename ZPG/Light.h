#pragma once
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

class Light : Subject
{
	 glm::vec3 lightPosition;
	 glm::vec3 lightColor;
	 glm::vec3 objectColor;

     vector<Observer*> observers;
public:
    Light(glm::vec3 lightPosition, glm::vec3 lightColor, glm::vec3 objectColor);

    glm::vec3 GetLightPosition();

    glm::vec3 GetLightColor();

    glm::vec3 GetObjectColor();

    void SetLightPosition(glm::vec3 newPosition);

    void SetLightColor(glm::vec3 newColor);

    void addObserver(Observer* observer) override;

    void notifyObservers() override;
};

