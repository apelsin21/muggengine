#ifndef SHADER_HPP
#define SHADER_HPP

#include <utility>

#include <GL/glew.h>

#include "file.hpp"
#include "defs.hpp"

namespace mugg {
    class Shader : public File {
        public:
            Shader();
            Shader(const Shader&) {}

            mugg::ShaderType type;
            GLuint id;
            bool compiled;
    };
}

#endif
