#include "shaderprogram.hpp"

mugg::core::ShaderProgram::ShaderProgram(const char* vsFilepath, const char* fsFilepath) {
    if(!mugg::io::LoadTextFromFile(vsFilepath, this->vsData)) {
        std::cout << "Failed to load vertex shader " << vsFilepath << " from disk.\n";
    }
    if(!mugg::io::LoadTextFromFile(fsFilepath, this->fsData)) {
        std::cout << "Failed to load fragment shader " << fsFilepath << " from disk.\n";
    }

    this->programID = glCreateProgram();
    this->vsID = glCreateShader(GL_VERTEX_SHADER);
    this->fsID = glCreateShader(GL_FRAGMENT_SHADER);
}


