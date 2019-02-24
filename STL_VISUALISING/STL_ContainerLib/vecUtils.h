#pragma once
#include <glm/glm.hpp>
#include <vector>
#include <numeric>

glm::vec3 average(const std::vector<glm::vec3>& v) {
    auto avg = std::accumulate(v.begin(), v.end(), glm::vec3(0., 0., 0.));
    float size = static_cast<float>(v.size());
    avg /= size;
    return avg;
}