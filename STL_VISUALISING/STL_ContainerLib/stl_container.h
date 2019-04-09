#pragma once
#include <vector>
#include <string>
#include "virtualModel.h"
#include <glm/glm.hpp>

class stl_container : public virtualModel
{
public:
    stl_container() = default;
    explicit stl_container(const char* fileName);
    void open(const char* fileName);
private:
    void centerize();
    void normalize(const float size);
    void readFile(const char* fileName);
    void readASCII(std::ifstream& file);
    void readBinary(std::ifstream& file);
    void recalculateNormals();
private:
    std::string name;
};