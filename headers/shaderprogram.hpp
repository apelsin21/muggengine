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
        //1: Vertex Shader
        //2: Fragment Shader
        //3: Geometry Shader
        //4: Tesselation Shader
        //5: Compute Shader
        mugg::Shader shaders[5];

    public:
        ShaderProgram();
        ~ShaderProgram();
    };
}

#endif
