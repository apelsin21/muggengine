#include "shader.hpp"

mugg::Shader::Shader() {
    this->compiled = false;
    this->type = mugg::VERTEX_SHADER;
    this->id = 0;
}

