#include "stdafx.h"
#include "Visualizer.h"
#include "stl_container.h"

using namespace glm;

#ifndef GL_USE
int mm()
#else
int main(int argc, char* argv[])
#endif 
{
    if (argc != 2)
    {
        std::cout << "enter file name" << std::endl;
        return 1;
    }
    stl_container container(argv[1]);
    Visualizer v(std::move(container));
    v.run();
    return 0;
}
