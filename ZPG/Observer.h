#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/fwd.hpp>

class Observer
{
public:
    virtual void update(const glm::mat4& viewMatrix, const glm::mat4& projectionMatrix) = 0;
};