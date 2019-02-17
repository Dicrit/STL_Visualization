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
    {
        openASCII(file);
        file.close();
    }
    else {
        file.close();
        file.open(fileName, std::fstream::binary);
        if (!file)
        {
            throw std::exception("Unable to open file");
        }
        openBinary(file);
        file.close();
    }
}

std::istream& operator>>(std::istream& is, glm::vec3 v)
{
    return is >> v.x >> v.y >> v.z;
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


class reader {
public:
    std::ifstream& _file;
    explicit reader(std::ifstream& file) : _file(file)
    {}
};

template <class T>
reader& operator>>(reader& r, T& val) {
    Read(&val, r._file);
    return r;
}


void stl_container::openBinary(std::ifstream& file)
{
    reader r(file);

    char buf[80];
    file.read(buf, 80);
    unsigned int size = 0;
    static_assert(sizeof(size) == 4, "size must be uint32.");
    r >> size;

    glm::vec3 v;
    static_assert(sizeof(v.x) == 4, "point coords must be float32");
    unsigned short attr;
    static_assert(sizeof(attr) == 2, "attributes must be ushort16");

    for (size_t i = 0; i < size; i++)
    {
        r >> v.x >> v.y >> v.z;
        normals.push_back(v);
        for (size_t j = 0; j < 3; j++)
        {
            r >> v.x >> v.y >> v.z;
            vertices.push_back(v);
        }
        r >> attr;
    }
}
