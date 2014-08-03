#ifndef CONTENTMANAGER_HPP
#define CONTENTMANAGER_HPP

#include <iostream>
#include <fstream>
#include <ostream>
#include <string>
#include <vector>
#include <algorithm>

#include <GL/glew.h>

#include <FreeImage.h>

#include <ft2build.h>
#include FT_FREETYPE_H

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "graphicsdefs.hpp"

#include "texture2d.hpp"
#include "shader.hpp"
#include "shaderprogram.hpp"

namespace mugg {
    namespace core {
        class Device;
        
        class ContentManager {
            private:
                std::ifstream inStream;
                std::ofstream outStream;
           
                std::vector<graphics::Texture2D*> textures;
                std::vector<graphics::Shader*> shaders;
                std::vector<graphics::ShaderProgram*> shaderPrograms;

                void ProcessAssimpScene(const aiScene*);
                void ProcessAssimpMesh(unsigned int, const aiMesh*);
                void ProcessAssimpMaterials(const aiScene*);

                void DeleteShaderID(GLuint);
                void DeleteTextureID(GLuint);
                void DeleteShaderProgramID(GLuint);

                bool SearchForID(std::vector<GLuint>&, GLuint, int&);
                GLint maxTextureSize;
            
                mugg::core::Device* creator;
            public:
                ContentManager(mugg::core::Device* device);
                ~ContentManager();

                virtual int GetMaxTextureSize();

                virtual mugg::graphics::Texture2D* CreateTexture2D(const std::string&, bool);
                
                virtual bool GetTextFile(const std::string, std::string&);
                
                virtual mugg::graphics::ShaderProgram* CreateShaderProgram();

                virtual mugg::graphics::Shader* CreateShader(mugg::graphics::ShaderType, const std::string&);
        };
    }
}

#endif
