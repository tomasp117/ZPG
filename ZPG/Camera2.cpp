#include "Camera2.h"

Camera2::Camera2(glm::vec3 position, glm::vec3 up, float fov, float ratio)
    : position(position), up(up), yaw(yaw), pitch(pitch), fov(fov), ratio(ratio), speed(2.5f)
{
    target = glm::vec3(0.0f);
    UpdateViewMatrix();
    UpdateProjectionMatrix();

}

glm::mat4 Camera2::getViewMatrix() const
{
    return this->viewMatrix;
}

glm::mat4 Camera2::getProjectionMatrix() const
{
    return this->projectionMatrix;
}

void Camera2::UpdateViewMatrix()
{
    viewMatrix = glm::lookAt(position, target, up);
}

void Camera2::UpdateProjectionMatrix()
{
    projectionMatrix = glm::perspective(glm::radians(fov), this->ratio, 0.0f, 100.0f);
}

void Camera2::addShader(ShaderProgram* shader)
{
    this->observers.push_back(shader);
}


void Camera2::moveForward(float velocity)
{
    position += target * velocity;
    UpdateViewMatrix();
    notifyObservers();
}

void Camera2::moveBackward(float velocity)
{
    position -= target * velocity;

    UpdateViewMatrix();

    notifyObservers();
}

void Camera2::moveRight(float velocity)
{
    glm::vec3 right = glm::normalize(glm::cross(target, up));

    position -= right * velocity;

    UpdateViewMatrix();
    notifyObservers();
    
}

void Camera2::moveLeft(float velocity)
{
    glm::vec3 right = glm::normalize(glm::cross(target, up));

    position += right * velocity;

    UpdateViewMatrix();

    notifyObservers();
}

void Camera2::rotate(float deltaX, float deltaY)
{
    yaw += deltaX;
    pitch += deltaY;

    if (pitch > 89.0f) pitch = 89.0f;
    if (pitch < -89.0f) pitch = -89.0f;


    glm::vec3 direction;

    direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    direction.y = sin(glm::radians(pitch));
    direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));

    target = glm::normalize(direction);

    UpdateViewMatrix();

    notifyObservers();
}

