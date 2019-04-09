#pragma once

class Controls
{
public:
    Controls(const glm::ivec2 window_resolution)
        :resolution(window_resolution)
    {
    }

    void computeMatricesFromInputs(GLFWwindow* window);
    glm::mat4 getViewMatrix();
    glm::mat4 getProjectionMatrix();
private:
    const glm::ivec2 resolution;
    glm::vec3 position = glm::vec3(0, 0, 5);

    float horizontalAngle = 3.14f;
    float verticalAngle = 0.0f;

    float FoV = 45.0f;

    float speed = 3.0f;
    float mouseSpeed = 0.005f;

    glm::vec3 direction;
    glm::vec3 right;


    double lastTime = 0;

    const float Pi = 3.14f;
};
