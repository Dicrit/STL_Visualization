#include "stdafx.h"

#include <glm/gtc/matrix_transform.hpp>
using namespace glm;

#include "controls.h"

glm::mat4 Controls::getViewMatrix()
{
    glm::vec3 up = glm::cross(right, direction);

    // Camera matrix
    return glm::lookAt(
        position,           // Camera is here
        position + direction, // and looks here : at the same position, plus "direction"
        up                  // Head is up (set to 0,-1,0 to look upside-down)
    );
}

glm::mat4 Controls::getProjectionMatrix()
{
    // Projection matrix : 45° Field of View, 4:3 ratio, display range : 0.1 unit <-> 100 units
    return glm::perspective(glm::radians(FoV), 4.0f / 3.0f, 0.1f, 100.0f);
}

void Controls::computeMatricesFromInputs(GLFWwindow* window)
{
    double currentTime = glfwGetTime();
    float deltaTime = float(currentTime - lastTime);

    // Get mouse position
    double xpos, ypos;
    glfwGetCursorPos(window, &xpos, &ypos);

    glfwSetCursorPos(window, resolution.x / 2, resolution.y / 2);

    horizontalAngle += mouseSpeed * float(resolution.x / 2 - xpos);
    verticalAngle += mouseSpeed * float(resolution.y / 2 - ypos);

    direction = glm::vec3(
        cos(verticalAngle) * sin(horizontalAngle),
        sin(verticalAngle),
        cos(verticalAngle) * cos(horizontalAngle)
    );

    right = glm::vec3(
        sin(horizontalAngle - Pi / 2.0f),
        0,
        cos(horizontalAngle - Pi / 2.0f)
    );


    if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) 
    {
        position += direction * deltaTime * speed;
    }

    if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) {
        position -= direction * deltaTime * speed;
    }

    if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS) {
        position += right * deltaTime * speed;
    }

    if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS) {
        position -= right * deltaTime * speed;
    }

    lastTime = currentTime;
}
