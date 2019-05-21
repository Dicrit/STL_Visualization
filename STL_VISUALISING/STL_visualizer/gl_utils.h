#pragma once
#include "stdafx.h"

template<typename T>
GLuint genericGenBuffer(std::vector<T> vec)
{
    GLuint vertexbuffer;
    glGenBuffers(1, &vertexbuffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
    glBufferData(GL_ARRAY_BUFFER, vec.size() * sizeof(T), &vec[0], GL_STATIC_DRAW);
    return vertexbuffer;
}
