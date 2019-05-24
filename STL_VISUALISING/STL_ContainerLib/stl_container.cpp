#include "stl_container.h"
#include <fstream>
#include "vecUtils.h"
#include <algorithm>

using glm::vec3;

namespace stl
{
    namespace model
    {
        stl_container::stl_container(const char * fileName)
        {
            open(fileName);
        }


        void stl_container::centerize()
        {
            auto avg = average(vertices);
            for (auto& v : vertices)
            {
                v -= avg;
            }
        }
        void stl_container::normalize(const float size) {
            glm::vec3 max = *std::max_element(vertices.begin(), vertices.end(), [](const vec3& v1, const vec3& v2) {return v1.length() < v2.length(); });
            float l = max.length();
            for (auto& v : vertices)
            {
                v = v * size / l;
            }
        }

        void stl_container::open(const char * fileName)
        {
            readFile(fileName);
            centerize();
            normalize(0.2);
        }

        void stl_container::readFile(const char * fileName)
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
                readASCII(file);
                file.close();
            }
            else {
                file.close();
                file.open(fileName, std::fstream::binary);
                if (!file)
                {
                    throw std::exception("Unable to open file");
                }
                readBinary(file);
                file.close();
            }
        }

        std::istream& operator>>(std::istream& is, glm::vec3& v)
        {
            return is >> v.x >> v.y >> v.z;
        }

        void stl_container::readASCII(std::ifstream& file)
        {
            std::string stub;
            std::getline(file, stub);
            glm::vec3 v{};
            while (true) {
                file >> stub;

                if (stub == "endsolid")
                {
                    break;
                }
                file >> stub; //normal
                file >> v;
                normals.push_back(v);
                normals.push_back(v);
                normals.push_back(v);
                file.get();//newline
                std::getline(file, stub);//outer loop

                for (size_t j = 0; j < 3; j++)
                {
                    file >> stub; //vertex
                    file >> v;
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


        reader& operator>>(reader& r, glm::vec3& v) {
            return r >> v.x >> v.y >> v.z;
        }

#define attr_t unsigned short
        glm::vec3 attr2rgb(attr_t attr)
        {
            attr_t r = attr, g = attr >> 5, b = attr >> 10;
            r &= (unsigned short)31;
            g &= (unsigned short)31;
            b &= (unsigned short)31;
            return glm::vec3(r / 31., g / 31., b / 31.);
        }

        void stl_container::readBinary(std::ifstream& file)
        {
            reader r(file);

            char buf[80];
            file.read(buf, 80);
            unsigned int size = 0;
            static_assert(sizeof(size) == 4, "size must be uint32.");
            r >> size;

            glm::vec3 v;
            static_assert(sizeof(v.x) == 4, "point coords must be float32");
            attr_t attr;
            static_assert(sizeof(attr) == 2, "attributes must be ushort16");

            for (size_t i = 0; i < size; i++)
            {
                r >> v;
                normals.push_back(v);
                normals.push_back(v);
                normals.push_back(v);
                for (size_t j = 0; j < 3; j++)
                {
                    r >> v;
                    vertices.push_back(v);
                }
                r >> attr;
                attr2rgb(attr);
                if (attr)
                    int a = 12;
            }
        }

        void stl_container::recalculateNormals()
        {
            normals.clear();
            normals.reserve(vertices.size() / 3);

            for (size_t i = 0; i < vertices.size(); i += 3)
            {
                auto a = vertices[i + 1] - vertices[i];
                auto b = vertices[i + 2] - vertices[i];
                auto cross = glm::cross(a, b);
                normals.push_back(glm::normalize(cross));
                normals.push_back(glm::normalize(cross));
                normals.push_back(glm::normalize(cross));
            }
        }

        std::vector<glm::vec3>& stl_container::getVertices()
        {
            return vertices;
        }

        std::vector<glm::vec3>& stl_container::getNormals()
        {
            return normals;
        }
    }
}
