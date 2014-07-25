#ifndef SHADERPROGRAM_HPP
#define SHADERPROGRAM_HPP

#include <iostream>
#include <string>
#include <vector>
#include <memory>

#include <GL/glew.h>

#include "fileutils.hpp"
#include "graphicsdefs.hpp"
#include "shader.hpp"
#include "globject.hpp"

namespace mugg {
    namespace graphics {
        class ShaderProgram : public GLObject {
            private:
                bool linked, hasGeneratedID, compiledSuccessfully;

                std::vector<std::shared_ptr<mugg::graphics::Shader>> shaders;
            public:
                ShaderProgram();
                ~ShaderProgram();
                
                bool HasGeneratedID();
                void DeleteID();
                void GenID();

                void CheckForErrors();
                const char* GetLog();
                bool Link();
                
                bool AddShader(std::shared_ptr<mugg::graphics::Shader>&);

                bool GetCompiledSuccessfully();

                bool Validate();

                GLint GetNumberOfAttachedShaders();
        };
    }
}

#endif
