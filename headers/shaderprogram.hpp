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
                
                virtual void CreateID();
                virtual void DeleteID();

                virtual void CheckForErrors();
                virtual const char* GetLog();
                virtual bool Link();
                
                virtual bool AttachShader(mugg::graphics::Shader*);

                virtual bool GetCompiledSuccessfully();

                virtual bool Validate();

                virtual bool AddAttribute(const std::string&);
                virtual GLint GetAttribute(const std::string&);

                virtual bool AddUniform(const std::string&);
                virtual GLint GetUniform(const std::string&);

                virtual GLint GetNumberOfAttachedShaders();

                virtual void Use();
        };
    }
}

#endif
