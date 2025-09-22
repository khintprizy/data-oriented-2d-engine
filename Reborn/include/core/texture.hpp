#pragma once
#include <GL/glew.h>
#include <string>

namespace core
{
    struct Texture2D {
        GLuint id = 0; 
        int width = 0, height = 0, channels = 0;

        bool loadFromFile(const std::string& path, bool flipY = true);
        void bind(int unit = 0) const;
    };
}