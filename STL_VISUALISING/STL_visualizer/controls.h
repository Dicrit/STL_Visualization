#pragma once

#include "InputProvider.h"

namespace stl {
    class Controls
    {
    public:
        explicit Controls(const glm::ivec2& window_resolution)
            : m_input(window_resolution)
        {
        }

        void computeMatricesFromInputs(GLFWwindow* window);
        glm::mat4 getViewMatrix();
        glm::mat4 getProjectionMatrix();
    private:
        glm::vec3 position = glm::vec3(0, 0, 5);

        float horizontalAngle = 3.14f;
        float verticalAngle = 0.0f;
        float radius = 10.0f;
        float FoV = 45.0f;

        float m_scaleSpeed = 6.0f;
        float m_rotationSpeed = 0.005f;

        stl::InputProvider m_input;
        double lastTime = 0;

        
        const float Pi = 3.14f;
    };
}
