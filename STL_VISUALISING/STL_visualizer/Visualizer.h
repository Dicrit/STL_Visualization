#pragma once
#include "stdafx.h"
#include "ScopeGuard.h"
#include "shader.h"
#include "controls.h"
#include "stl_container.h"
#include "gl_utils.h"


class Visualizer
{
public:
    explicit Visualizer(stl_container container);
    int run();
private:
    stl_container m_container;
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


    void initVNU();

    void LoadMVP();

    void initGLFW();

    void cleanup();

    void initGLEW();

    void setupEnv();
    
};