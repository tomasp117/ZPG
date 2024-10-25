#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Transformation
{
private:
    glm::mat4 modelMatrix;

public:
    // Getter for the transformation matrix
    glm::mat4& getMatrix();

    // Transformation functions
    Transformation();
    void translate(const glm::vec3& translation);
    void rotate(float angle, const glm::vec3& axis);
    void scale(const glm::vec3& scale);


};

