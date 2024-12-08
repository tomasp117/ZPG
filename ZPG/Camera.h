#pragma once

// PRO0366 Tomáš Prorok 

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <vector>
#include "ShaderProgram.h"

//Include the standard C++ headers  
#include <stdlib.h>
#include <stdio.h>
#include <vector>
#include "Subject.h"

class Camera : Subject
{
private:
    // Camera attributes
    glm::vec3 position;                         //Camera positon in world
    glm::vec3 target;                           // Point where camera is pointing to
    glm::vec3 up;                               // Vector that determines the cameras tilt
    glm::vec3 right;                            // Right vector (something like up)

	float ratio;								// Aspect ratio
	float speed;								// Camera speed

	int width;                                  // Window width
	int height;								    // Window height

    // Camera settings
    float yaw;                                  // Yaw rotation angle (horizontal)
    float pitch;                                // Pitch rotation angle (vertical)
    float fov;                                  // Field of view


    glm::mat4 viewMatrix;                       // Transforms coordinates from world/global space to camera/local space
    glm::mat4 projectionMatrix;                 // Perspective

    std::vector<Observer*> observers;           // List of observers that need to be notified on camera changes


public:
    // Constructor
    Camera(glm::vec3 position, glm::vec3 up, float fov, float ratio);

    // Getters
    glm::mat4 getViewMatrix();
	glm::mat4 getProjectionMatrix();
    void updateProjectionMatrix(float aspectRatio); // Updates the view matrix based on position, target, and up vector with lookAt function
	glm::vec3 getPosition(); 
	glm::vec3 getTarget(); 
	int getWidth(); 
	int getHeight();

	// Setters
	void setWidth(int width);
	void setHeight(int height);
    
	// Camera initialization
    void updateViewMatrix();                    // Updates the view matrix based on position, target, and up vector with lookAt function
    void updateProjectionMatrix();              // Updates the projection matrix based on FOV and ratio with perspective function

	// Camera movement and rotation
    void moveForward(float velocity);           // W
    void moveBackward(float velocity);          // S
    void moveRight(float velocity);             // D
    void moveLeft(float velocity);              // A
    void rotate(float deltaX, float deltaY);    // Mouse button two hold 

    // Observer pattern functions to add observers and notify them of changes
    void addObserver(Observer* observer) override;
    void removeObserver(Observer* observer) override;
    void notifyObservers() override;

};

