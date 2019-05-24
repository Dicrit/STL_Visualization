#include "stdafx.h"
#include "Visualizer.h"
#include "stl_container.h"
#include <Windows.h>

using namespace glm;

#ifndef GL_USE
int mm()
#else
int main(int argc, char* argv[])
#endif 
{
    if (argc != 2)
    {
        std::cout << "File name is absent" << std::endl;
        return 1;
    }
    int result = 0;
    stl::model::stl_container container;
    try
    {
        std::cout << "Loading model..." << std::endl;
        container.open(argv[1]);
        std::cout << "Model has been loaded." << std::endl;
        std::cout << "Starting visualization..." << std::endl;
        stl::visualization::Visualizer v(std::move(container));
        result = v.run();
    }
    catch (const std::exception& ex)
    {
        std::cout << "error happened while run program: " << ex.what() << std::endl;
        if (::IsDebuggerPresent())
        {
            system("pause");
        }
    }

    return result;
}
