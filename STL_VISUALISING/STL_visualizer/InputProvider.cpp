#include "stdafx.h"
#include "InputProvider.h"



stl::InputProvider::InputProvider(const glm::ivec2& window_resolution)
    : resolution(window_resolution)
{
}

void stl::InputProvider::getInputAxes(GLFWwindow * window, float & horizontal, float & vertical)
{
    // Get mouse position
    double xpos, ypos;
    glfwGetCursorPos(window, &xpos, &ypos);

    glfwSetCursorPos(window, resolution.x / 2, resolution.y / 2);

    horizontal = float(resolution.x / 2 - xpos);
    vertical = float(resolution.y / 2 - ypos);
}
