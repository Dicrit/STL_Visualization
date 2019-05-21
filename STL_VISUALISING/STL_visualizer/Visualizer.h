#pragma once
#include "stdafx.h"
#include "ScopeGuard.h"
#include "shader.h"
#include "controls.h"
#include "stl_container.h"
#include "gl_utils.h"

namespace stl
{
    namespace visualization
    {
        class Visualizer
        {

        public:
            template <class model_type>
            explicit Visualizer(model_type&& container)
                : resolution(glm::ivec2(1024, 768))
                , controls(resolution)
                , vertices(container.getVertices())
                , normals(container.getNormals())
            {
            }

            int run();
        private:
            //stl_container m_container;
            GLFWwindow* window;

            const glm::vec3 lightPos = glm::vec3(4, 4, 4);

            std::vector<glm::vec3> vertices;
            std::vector<glm::vec3> normals;
            GLuint MatrixID;
            GLuint ViewMatrixID;
            GLuint ModelMatrixID;

            GLuint vertexbuffer;
            GLuint normalbuffer;

            GLuint VertexArrayID;

            GLuint programID;

            const glm::ivec2 resolution;

            Controls controls;

            void LoadMVP();

            void initGLFW();

            void cleanup();

            void initGLEW();

            void setupEnv();

        };
    }
}
