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
    namespace core {
        class ContentManager;
    }

    namespace graphics {
        class ShaderProgram : public GLObject {
            private:
                bool linked, hasGeneratedID, compiledSuccessfully;

                std::vector<GLuint> shaders;
                mugg::core::ContentManager* creator;
            public:
                ShaderProgram();
                ShaderProgram(mugg::core::ContentManager*);
                ~ShaderProgram();
                
                bool HasGeneratedID();
                void DeleteID();
                void GenID();

                void CheckForErrors();
                const char* GetLog();
                bool Link();
                
                bool AddShader(GLuint);

                bool GetCompiledSuccessfully();

                bool Validate();

                GLint GetNumberOfAttachedShaders();
        };
    }
}

#endif
