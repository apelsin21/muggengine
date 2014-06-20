#ifndef SHADERPROGRAM_HPP
#define SHADERPROGRAM_HPP

#include <iostream>
#include <string>
#include <vector>

#include <GL/glew.h>

#include "fileutils.hpp"
#include "graphicsdefs.hpp"
#include "shader.hpp"

namespace mugg {
    namespace graphics {
        class ShaderProgram {
            private:
                GLuint ID;
                bool linked, hasGeneratedID, compiledSuccessfully;

                std::vector<mugg::graphics::Shader> shaderVector;
            public:
                ShaderProgram();
                ~ShaderProgram();
                
                GLuint GetID();
                bool HasGeneratedID();
                void DeleteID();
                void GenID();

                void CheckForErrors();
                const char* GetLog();
                bool Link();
                
                bool AddShader(mugg::graphics::Shader shader);
                bool AddShader(mugg::graphics::ShaderType type, const char* filepath);

                bool GetCompiledSuccessfully();

                bool Validate();

                GLint GetNumberOfAttachedShaders();
        };
    }
}

#endif
