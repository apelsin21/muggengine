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

        bool CompileShader(mugg::Shader shader);
        mugg::Shader LoadShader(std::string filepath, mugg::ShaderType type);

        bool linked;
    public:
        void AddShader(std::string filepath, mugg::ShaderType type);
        
        mugg::Shader GetShaderByType(mugg::ShaderType type);
    
        
    };
}

#endif
