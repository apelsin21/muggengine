#ifndef SHADER_HPP
#define SHADER_HPP

#include "GL/glew.h"

#include "file.hpp"
#include "defs.hpp"

namespace mugg {
    class Shader : public File {
        public:
            mugg::ShaderType type; 
            GLuint id;
            bool compiled = false;
    };
}

#endif
