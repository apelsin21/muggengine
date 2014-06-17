#ifndef SHADERPROGRAM_HPP
#define SHADERPROGRAM_HPP

#include <iostream>

#include <GL/glew.h>

#include "fileutils.hpp"

namespace mugg {
    namespace core {
        class ShaderProgram {
            private:
                GLuint programID, vsID, fsID;
                std::string vsData, fsData;
                bool linked;

                bool AddShaders(const char* vsFilepath, const char* fsFilepath);
                void CompileShader(GLuint shaderID, const char* data);
                bool CheckProgramForError();
                //Returns true on success, false on failure
                bool CheckShaderForError(GLuint shaderID);
            public:
                ShaderProgram(const char* vsFilepath, const char* fsFilepath);
                ~ShaderProgram();

               
                bool Link();

                GLuint GetProgramID();
        };
    }
}

#endif
