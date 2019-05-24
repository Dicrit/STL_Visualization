#include "stdafx.h"
#include <glm/gtc/matrix_transform.hpp>
#include "controls.h"

using namespace glm;
namespace stl
{
    glm::mat4 Controls::getViewMatrix()
    {
        const glm::vec3 c_up(0.0f, 0.0f, 1.0f);
        glm::vec3 right = glm::cross(c_up, position);
        glm::vec3 up = glm::cross(position, right);

        return glm::lookAt(
            position,           // Camera is here
            glm::vec3(),        // and looks here
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

        float horizontal = 0;
        float vertical = 0;
        m_input.getInputAxes(window, horizontal, vertical);

        horizontalAngle += m_rotationSpeed * horizontal;
        verticalAngle = glm::clamp(verticalAngle - m_rotationSpeed * vertical, -Pi / 2.0f, Pi / 2.0f);

        position.x = glm::cos(horizontalAngle) * glm::cos(verticalAngle) * radius;
        position.y = glm::sin(horizontalAngle) * glm::cos(verticalAngle) * radius;
        position.z = glm::sin(verticalAngle) * radius;

        if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
        {
            radius -= deltaTime * m_scaleSpeed;
        }

        if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
        {
            radius += deltaTime * m_scaleSpeed;
        }
        if (radius < 0)
            radius = 0.000001f;

        lastTime = currentTime;
    }
}
