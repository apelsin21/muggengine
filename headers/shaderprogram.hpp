#ifndef SHADERPROGRAM_HPP
#define SHADERPROGRAM_HPP

#include <vector>
#include <string>

#include <GL/glew.h>

#include "shader.hpp"
#include "log.hpp"
#include "filehandler.hpp"

namespace mugg {
    class ShaderProgram {
    private:
        mugg::Filehandler filehandler;
        std::vector<mugg::Shader> shaders;
        GLuint id;
        bool linked;

        bool CompileShader(mugg::Shader shader);
        mugg::Shader LoadShader(std::string filepath, mugg::ShaderType type);
    public:
        ShaderProgram();
        ShaderProgram(const mugg::ShaderProgram& name) {}
        ~ShaderProgram();

        bool AddShader(std::string filepath, mugg::ShaderType type);

        mugg::Shader GetShaderByType(mugg::ShaderType type);

        bool LinkProgram();
    };
}

#endif
