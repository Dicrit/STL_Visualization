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
	void openASCII(std::ifstream& file);
	void openBinary(std::ifstream& file);
private:
	std::string name;
};