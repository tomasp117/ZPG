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

#include <random>
#include <time.h>
#include "Scene.h"

using namespace std;

class SceneManager
{
private:
	float ratio;
	int active_scene;
	vector<Scene*> scenes;
public:
	SceneManager(float ratio);
	void initScene1();
	void initScene2();
	void initScene3();
	void initScene4();
	Scene* getActiveScene();
	void switchScene(); 

	vector<Scene*> getScenes();
};

