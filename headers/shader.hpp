#ifndef SHADER_HPP
#define SHADER_HPP

#include "GL/glew.h"

#include "file.hpp"
#include "defs.hpp"

namespace mugg {
    class Shader : public File {
        public:
            Shader() {this->compiled = false; this->type = mugg::VERTEX_SHADER; this->id = 0;}
            Shader(const Shader&) {}
            ~Shader() {}

            mugg::ShaderType type;
            GLuint id;
            bool compiled;
    };
}

#endif
