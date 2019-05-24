#pragma once
#include <glm/glm.hpp>
#include <vector>

namespace stl
{
    namespace model
    {
        class virtualModel
        {
        public:
            virtualModel();
            virtual ~virtualModel();

            virtual std::vector<glm::vec3>& getVertices() = 0;
            virtual std::vector<glm::vec3>& getNormals() = 0;
        };
    }
}
