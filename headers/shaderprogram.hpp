#ifndef SHADERPROGRAM_HPP
#define SHADERPROGRAM_HPP

#include <vector>
#include <string>

#include <GL/glew.h>

#include "shader.hpp"
#include "log.hpp"
#include "filehandler.hpp"
#include <cstdlib>
#include <cstring>

namespace mugg {
    class ShaderProgram {
    private:
        mugg::Filehandler filehandler;
        std::vector<mugg::Shader> shaders;
        GLuint id;
        bool linked;

        bool CompileShader(mugg::Shader &shader);
        bool LoadShader(std::string filepath, mugg::ShaderType type, mugg::Shader &outShader);
    public:
        ShaderProgram();
        ShaderProgram(const mugg::ShaderProgram& name) {}
        ~ShaderProgram();

        bool AddShader(std::string filepath, mugg::ShaderType type);

        bool LoadShadersFromDisk();

        bool GetShaderByType(mugg::ShaderType type);

        bool LinkProgram();
    };
}

#endif
