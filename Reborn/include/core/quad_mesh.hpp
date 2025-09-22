#pragma once
#include <GL/glew.h>

namespace core
{
    struct QuadMesh {
        GLuint vao = 0, vbo = 0, ebo = 0;
        void create();
        void draw() const;
    };
}
