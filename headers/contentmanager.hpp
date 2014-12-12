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

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "graphicsdefs.hpp"

#include "texture2d.hpp"
#include "shader.hpp"
#include "shaderprogram.hpp"
#include "mesh.hpp"

namespace mugg {
    namespace core {
        class Engine;
        
        class ContentManager {
            private:
                std::ifstream inStream;
                std::ofstream outStream;
           
                std::vector<graphics::Texture2D*> textures;
                std::vector<graphics::Shader*> shaders;
                std::vector<graphics::ShaderProgram*> shaderPrograms;
                std::vector<graphics::Mesh*> meshes;

                void ProcessAssimpScene(const aiScene*);
                void ProcessAssimpMesh(unsigned int, const aiMesh*);
                void ProcessAssimpMaterials(const aiScene*);

                void DeleteShaderID(GLuint);
                void DeleteTextureID(GLuint);
                void DeleteShaderProgramID(GLuint);

                bool SearchForID(std::vector<GLuint>&, GLuint, int&);
                GLint maxTextureSize;
            
                mugg::core::Engine* parent;
            public:
                ContentManager(mugg::core::Engine* Engine);
                ~ContentManager();

                int GetMaxTextureSize();

                mugg::graphics::Texture2D* CreateTexture2D(const std::string&, bool);
                
                bool GetTextFile(const std::string, std::string&);
                
                mugg::graphics::ShaderProgram* CreateShaderProgram();

                mugg::graphics::Shader* CreateShader(mugg::graphics::ShaderType, const std::string&);
        
                mugg::graphics::Mesh* CreateMesh(const std::string&);
        };
    }
}

#endif
