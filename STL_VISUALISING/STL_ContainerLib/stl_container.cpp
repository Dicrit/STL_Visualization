#include "stl_container.h"
#include <fstream>

stl_container::stl_container(const char * fileName)
{
	open(fileName);
}

void stl_container::open(const char * fileName)
{
	std::ifstream file;

	file.open(fileName);
	if (!file)
	{
		throw std::exception("Unable to open file");
	}
	const int bufsize = 5;
	char buf[bufsize];
	file.read(buf, bufsize);
	if (std::equal(buf, &buf[bufsize], "solid"))
		openASCII(file);
	else
		openBinary(file);
}

void stl_container::openASCII(std::ifstream& file)
{
	std::string stub;
	std::getline(file, stub);
	glm::vec3 v;
	while (true) {
		file >> stub;
		
		if (stub == "endsolid")
		{
			break;
		}

		file >> stub; //normal
		file >> v.x >> v.y >> v.z; //reading normal
		normals.push_back(v);
		file.get();//newline
		std::getline(file, stub);//outer loop
		
		for (size_t j = 0; j < 3; j++)
		{
			file >> stub; //vertex
			file >> v.x >> v.y >> v.z;
			vertices.push_back(v);

		}
		file.get(); //newline
		std::getline(file, stub); //endloop
		std::getline(file, stub); //endfacet
	}
}
template <class T>
void Read(T* res, std::ifstream&file)
{
	char buf[sizeof(T)];
	file.read(buf, sizeof(T));
	*res = *reinterpret_cast<T*>(&buf[0]);
}

void stl_container::openBinary(std::ifstream& file)
{
	char buf[74];
	file.read(buf, 74);
	unsigned int sz = 0;
	Read(&sz, file);
}
