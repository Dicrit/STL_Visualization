#include "virtualModel.h"



virtualModel::virtualModel()
{
}


virtualModel::~virtualModel()
{
}

std::vector<glm::vec3>& virtualModel::getVertices()
{
    return vertices;
}

std::vector<glm::vec3>& virtualModel::getNormals()
{
    return normals;
}
