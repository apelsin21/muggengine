#ifndef SHADERPROGRAM_HPP
#define SHADERPROGRAM_HPP

#include <iostream>
#include <string>
#include <vector>
#include <map>
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
                bool linked, compiledSuccessfully;

                std::vector<GLuint> shaders;

                std::map<std::string, GLint> knownLocations;

                mugg::core::ContentManager* creator;
            public:
                ShaderProgram(bool);
                ShaderProgram(mugg::core::ContentManager*);
                ~ShaderProgram();
                
                void CreateID();
                void DeleteID();

                void CheckForErrors();
                const char* GetLog();
                bool Link();
                
                bool AttachShader(mugg::graphics::Shader*);

                bool GetCompiledSuccessfully();

                bool Validate();

                bool AddAttrib(const std::string&);
                GLint GetAttrib(const std::string&);

                bool AddUniform(const std::string&);
                GLint GetUniform(const std::string&);

                GLint GetNumberOfAttachedShaders();

                void Use();
        };
    }
}

#endif
