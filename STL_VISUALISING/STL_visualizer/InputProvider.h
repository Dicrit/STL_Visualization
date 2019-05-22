#pragma once
#include "stdafx.h"

namespace stl
{
    class InputProvider
    {
    public:
        InputProvider(const glm::ivec2& window_resolution);
        void getInputAxes(GLFWwindow* window, float &horizontal, float& vertical);
    private:
        double lastTime = 0;
        const glm::ivec2 resolution;
    };
}
