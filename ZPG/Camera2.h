#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <vector>
#include "ShaderProgram.h"

//Include the standard C++ headers  
#include <stdlib.h>
#include <stdio.h>
#include <vector>

#include "Subject.h"

class ShaderProgram;

class Camera2 : Subject
{
private:
    // Camera attributes
    glm::vec3 position;
    glm::vec3 target;
    glm::vec3 up;
    glm::vec3 right;

    float ratio;
    float speed;

    // Camera settings
    float yaw;
    float pitch;
    float fov;


    glm::mat4 viewMatrix;
    glm::mat4 projectionMatrix;

    std::vector<ShaderProgram*> observers;

    //std::vector<ShaderProgram*> shaders;

public:
    Camera2(glm::vec3 position, glm::vec3 up, float fov, float ratio);
    glm::mat4 getViewMatrix() const;
    glm::mat4 getProjectionMatrix() const;

    void UpdateViewMatrix();
    void UpdateProjectionMatrix();

    void addShader(ShaderProgram* shader);
    // Pohyb kamery
    void moveForward(float velocity);
    void moveBackward(float velocity);
    void moveRight(float velocity);
    void moveLeft(float velocity);
    void rotate(float deltaX, float deltaY);
};

