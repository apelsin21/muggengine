#ifndef SHADERPROGRAM_HPP
#define SHADERPROGRAM_HPP

#include <iostream>

#include <GL/glew.h>

#include "fileutils.hpp"

namespace mugg {
    namespace core {
        class ShaderProgram {
            private:
                GLuint programID, vsID, fsID;
                std::string vsData, fsData;
                bool compiled;
            public:
                ShaderProgram(const char* vsFilepath, const char* fsFilepath);
                ShaderProgram();
                ~ShaderProgram();


        };
    }
}

#endif
