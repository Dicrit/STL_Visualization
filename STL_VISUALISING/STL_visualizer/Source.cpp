#include <iostream>
#include "stl_container.h"


stl_container container;


int mainG()
{
	container.open("C:\\Users\\Dicrit_note\\Documents\\Dima\\Курсовая\\Snowman_ascii.stl");

	for (auto v : container.getVertices())
	{
		std::cout << v.x << " - " << v.y << " - " << v.z << std::endl;
	}
	std::cout << "vettices end\n";


	//std::cin.get();


	for (auto v : container.getNormals())
	{
		std::cout << v.x << " - " << v.y << " - " << v.z << std::endl;
	}

	//std::cin.get();



	return 0;
}
