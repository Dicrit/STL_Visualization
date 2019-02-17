#include "stdafx.h"
#include <iostream>
#include "stl_container.h"


stl_container container;

#ifdef GL_USE
int mm()
#else
int main()
#endif 
{
    try
    {
        if (0)
            container.open("..\\..\\Snowman_ascii.stl");
        else
            container.open("..\\..\\Snowman2.stl");
    }
    catch (const std::exception& e)
    {
        std::cout << "Can't open file. " << e.what();
        return 1;
    }
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
