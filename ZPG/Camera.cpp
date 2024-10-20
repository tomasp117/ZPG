#include "Camera.h"

Camera::Camera(glm::vec3 position, glm::vec3 up, float yaw, float pitch, float fov, float ratio)
    : position(position), up(up), yaw(yaw), pitch(pitch), fov(fov), ratio(ratio), speed(2.5f)
{
    updateCameraVectors();
}

glm::mat4 Camera::getViewMatrix() const
{
	return this->viewMatrix;
}

glm::mat4 Camera::getProjectionMatrix(float aspectRatio) const
{
    return this->projectionMatrix;
}

void Camera::updateCameraVectors()
{
    glm::vec3 front;
    front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    front.y = sin(glm::radians(pitch));
    front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    target = glm::normalize(front);

    right = glm::normalize(glm::cross(target, up));       
    up = glm::normalize(glm::cross(right, target));   

    viewMatrix = glm::lookAt(position, position + target, up);
    projectionMatrix = glm::perspective(glm::radians(fov), this->ratio, 0.1f, 100.0f);
}

void Camera::UpdateViewMatrix()
{
    viewMatrix = glm::lookAt(position, position + target, up);
}

void Camera::UpdateProjectionMatrix()
{
    projectionMatrix = glm::perspective(glm::radians(fov), ratio, 0.1f, 100.0f);
}

void Camera::addObserver(Observer* observer)
{
    observers.push_back(observer);
}

void Camera::removeObserver(Observer* observer)
{
    auto it = std::remove(observers.begin(), observers.end(), observer);
    observers.erase(it, observers.end());
}

void Camera::notifyObservers()
{
    for (Observer* observer : observers)
    {
        observer->update(viewMatrix, projectionMatrix);
    }
}

void Camera::moveForward(float velocity)
{
    position += target * speed * velocity; // Use speed here
    updateCameraVectors();
    notifyObservers();
}

void Camera::moveBackward(float velocity)
{
    position -= target * speed * velocity; // Use speed here
    updateCameraVectors();
    notifyObservers();
}

void Camera::moveRight(float velocity)
{
    position += right * speed * velocity; // Use speed here
    updateCameraVectors();
    notifyObservers();
}

void Camera::moveLeft(float velocity)
{
    position -= right * speed * velocity; // Use speed here
    updateCameraVectors();
    notifyObservers();
}

void Camera::rotate(float deltaX, float deltaY)
{
    yaw += deltaX;
    pitch += deltaY;

    // Limit the pitch to prevent screen flipping
    if (pitch > 89.0f)
        pitch = 89.0f;
    if (pitch < -89.0f)
        pitch = -89.0f;

    // Update the front, right, and up vectors based on the updated angles
    updateCameraVectors();
    notifyObservers();
}

void Camera::update(const glm::mat4& viewMatrix, const glm::mat4& projectionMatrix)
{
    // V tomto pøípadì možná nemusíš dìlat nic v samotné metodì update()
    // Kamera nebude mìnit svou interní logiku, ale po každé zmìnì pøepoèítá matice
}
