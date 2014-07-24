#ifndef SHADER_HPP
#define SHADER_HPP

#include <GL/glew.h>

#include <iostream>
#include <string>
#include <memory>

#include "graphicsdefs.hpp"
#include "fileutils.hpp"
#include "renderable.hpp"

namespace mugg {
    namespace graphics {
        class Shader : public Renderable {
            private:
                mugg::graphics::ShaderType type;
                const char* filepath;
                std::string data;
                bool loaded, hasGeneratedID, compiledSuccessfully;
                
                void CheckForErrors();
                const char* GetLog();
                bool Validate();
            public:
                Shader();
                ~Shader();

                void GenID();

                void DeleteID();

                mugg::graphics::ShaderType GetType();
                void SetType(mugg::graphics::ShaderType);

                std::string GetData();
                void SetData(const std::string& data = "");

                const char* GetFilepath();
                void SetFilepath(const char* filepath = "");

                bool GetLoaded();
                bool GetCompiledSuccessfully();

                bool Load(const char* filepath);
                bool Load(mugg::graphics::ShaderType, const char*);

                bool Compile();
        };
    }
}

#endif
