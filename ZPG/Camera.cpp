#include "Camera.h"

Camera::Camera(glm::vec3 position, glm::vec3 up, float fov, float ratio)
{
    this->position = position;
    this->up = up;
    this->fov = fov;
    this->ratio = ratio;

    // Default target location and speed
    this->speed = 7.0f;
    this->target = glm::vec3(0.1f, 0.1f, 0.1f); 

    // Default horizpntal and vertical rotation
    this->yaw = 0.0f;
    this->pitch = 0.0f;

    // Initialize matrices based on the current settings
    updateViewMatrix(); 
    updateProjectionMatrix();
}

glm::mat4 Camera::getViewMatrix()
{
    return this->viewMatrix;
}

glm::mat4 Camera::getProjectionMatrix()
{
    return this->projectionMatrix;
}

void Camera::updateViewMatrix()
{
    this->viewMatrix = glm::lookAt(this->position, this->position + this->target, this->up);
}

void Camera::updateProjectionMatrix()
{
    this->projectionMatrix = glm::perspective(glm::radians(this->fov), this->ratio, 0.1f, 100.0f); // near = min distance from camera to objects for rendering / far = max distance
}

void Camera::updateProjectionMatrix(float aspectRatio)
{
    this->projectionMatrix = glm::perspective(glm::radians(this->fov), aspectRatio, 0.1f, 100.0f); // near = min distance from camera to objects for rendering / far = max distance
    notifyObservers();
}
glm::vec3 Camera::getPosition()
{
    return this->position;
}

glm::vec3 Camera::getTarget()
{
    return this->target;
}

int Camera::getWidth()
{
	return this->width;
}

int Camera::getHeight()
{
	return this->height;
}

void Camera::setWidth(int width)
{
	this->width = width;
}

void Camera::setHeight(int height)
{
	this->height = height;
}

void Camera::moveForward(float velocity)
{
    this->position += this->target * (velocity * this->speed);
    updateViewMatrix();
    notifyObservers();
}

void Camera::moveBackward(float velocity)
{
    this->position -= this->target * (velocity * this->speed);

    updateViewMatrix();

    notifyObservers();
}

void Camera::moveRight(float velocity)
{
    this->right = glm::normalize(glm::cross(this->target, this->up));

    this->position += this->right * (velocity * this->speed);

    updateViewMatrix();
    notifyObservers();

}

void Camera::moveLeft(float velocity)
{
    this->right = glm::normalize(glm::cross(this->target, this->up));

    this->position -= this->right * (velocity * this->speed);

    updateViewMatrix();
    notifyObservers();
}

void Camera::rotate(float deltaX, float deltaY)
{
    this->yaw += deltaX;
    this->pitch += deltaY;

    // Clamp the pitch angle to avoid gimbal lock
    if (this->pitch > 89.0f) this->pitch = 89.0f;
    if (this->pitch < -89.0f) this->pitch = -89.0f;

    // Calculate the new target direction based on yaw and pitch angles
    glm::vec3 direction;
    direction.x = cos(glm::radians(this->yaw)) * cos(glm::radians(this->pitch));
    direction.y = sin(glm::radians(this->pitch));
    direction.z = sin(glm::radians(this->yaw)) * cos(glm::radians(this->pitch));
    this->target = glm::normalize(direction);

    updateViewMatrix();
    notifyObservers();
}

void Camera::addObserver(Observer* observer)
{
    observers.push_back(observer);
}

void Camera::notifyObservers() {
    for (Observer* observer : observers) {
        observer->update(this);
    }
}