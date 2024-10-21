#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/fwd.hpp>
#include "Observer.h"
#include <vector>
class Camera : public Observer
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

    std::vector<Observer*> observers;

    glm::mat4 viewMatrix;
    glm::mat4 projectionMatrix;

public:
    Camera(glm::vec3 position, glm::vec3 up, float yaw, float pitch, float fov, float ratio);
    glm::mat4 getViewMatrix() const;
    glm::mat4 getProjectionMatrix(float aspectRatio) const;
    void updateCameraVectors();

    void UpdateViewMatrix();
    void UpdateProjectionMatrix();

    void addObserver(Observer* observer);  // Metoda pro pøidání observera
    void removeObserver(Observer* observer);  // Metoda pro odebrání observera
    void notifyObservers();  // Notifikace observerù

    void moveForward(float velocity);
    void moveBackward(float velocity);
    void moveRight(float velocity);
    void moveLeft(float velocity);

    void rotate(float deltaX, float deltaY);
    //void update(const glm::mat4& viewMatrix, const glm::mat4& projectionMatrix) override;
};

