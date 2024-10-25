#include "Camera.h"

Camera::Camera(glm::vec3 position, glm::vec3 up, float fov, float ratio)
    : position(position), up(up), yaw(-90.0f), pitch(0.0f), fov(fov), ratio(ratio), speed(5.0f)
{
    target = glm::vec3(0.0f, 0.0f, 0.0f);
    UpdateViewMatrix();
    UpdateProjectionMatrix();

}

glm::mat4 Camera::getViewMatrix()
{
    return this->viewMatrix;
}

glm::mat4 Camera::getProjectionMatrix()
{
    return this->projectionMatrix;
}

void Camera::UpdateViewMatrix()
{
    viewMatrix = glm::lookAt(position, this->position + target, up);
}

void Camera::UpdateProjectionMatrix()
{
    projectionMatrix = glm::perspective(glm::radians(fov), this->ratio, 0.1f, 100.0f);
}
/*
void Camera::addShader(ShaderProgram* shader)
{
    this->observers.push_back(shader);
}*/


void Camera::moveForward(float velocity)
{
    position += target * (velocity * speed);
    UpdateViewMatrix();
    notifyObservers();
}

void Camera::moveBackward(float velocity)
{
    position -= target * (velocity * speed);

    UpdateViewMatrix();

    notifyObservers();
}

void Camera::moveRight(float velocity)
{
    glm::vec3 right = glm::normalize(glm::cross(target, up));

    position += right * (velocity * speed);

    UpdateViewMatrix();
    notifyObservers();

}

void Camera::moveLeft(float velocity)
{
    glm::vec3 right = glm::normalize(glm::cross(target, up));

    position -= right * (velocity * speed);

    UpdateViewMatrix();

    notifyObservers();
}

void Camera::rotate(float deltaX, float deltaY)
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

void Camera::addObserver(Observer* observer)
{
    observers.push_back(observer);
    //notifyObservers();
}

void Camera::notifyObservers() {
    for (Observer* observer : observers) {
        observer->update();
    }
}