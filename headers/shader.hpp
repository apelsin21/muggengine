#ifndef SHADER_HPP
#define SHADER_HPP

#include <GL/glew.h>

#include <iostream>
#include <string>

#include "graphicsdefs.hpp"
#include "fileutils.hpp"

namespace mugg {
    namespace graphics {
        class Shader {
            private:
                mugg::graphics::ShaderType type;
                GLuint ID;
                const char* filepath;
                std::string data;
                bool loaded, hasGeneratedID, compiledSuccessfully;
                
                void CheckForErrors();
                const char* GetLog();
                bool Validate();
            public:
                Shader();
                Shader(mugg::graphics::ShaderType type, const char* filepath);
                ~Shader();

                void GenID();

                GLuint GetID();
                void DeleteID();

                mugg::graphics::ShaderType GetType();
                void SetType(mugg::graphics::ShaderType type);

                std::string GetData();
                void SetData(std::string data);

                const char* GetFilepath();
                void SetFilepath(const char* filepath);

                bool GetLoaded();
                bool GetCompiledSuccessfully();

                bool LoadFromFilepath(const char* filepath);

                bool Compile();
        };
    }
}

#endif
