#pragma once
#include <glm/glm.hpp>
#include <vector>

class virtualModel
{
public:
    virtualModel();
    virtual ~virtualModel();

    std::vector<glm::vec3>& getVertices();
    std::vector<glm::vec3>& getNormals();
protected:
    std::vector<glm::vec3> vertices;
    std::vector<glm::vec3> normals;
};

