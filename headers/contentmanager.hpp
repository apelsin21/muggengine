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

#include "texture2d.hpp"
#include "shader.hpp"
#include "graphicsdefs.hpp"
#include "shaderprogram.hpp"

namespace mugg {
    namespace core {
        class ContentManager {
            private:
                std::ifstream inStream;
                std::ofstream outStream;
           
                std::vector<GLuint> textures;
                std::vector<GLuint> shaders;
                std::vector<GLuint> shaderPrograms;

                void ProcessAssimpScene(const aiScene*);
                void ProcessAssimpMesh(unsigned int, const aiMesh*);
                void ProcessAssimpMaterials(const aiScene*);

                void DeleteShaderID(GLuint);
                void DeleteTextureID(GLuint);
                void DeleteShaderProgramID(GLuint);

                bool SearchForID(std::vector<GLuint>&, GLuint, int&);

                ContentManager() {};
                ContentManager(ContentManager const&);
                void operator=(ContentManager const&);
            public:
                static ContentManager& GetInstance() {
                    static ContentManager instance;
                    return instance;
                }
                ~ContentManager();

                mugg::graphics::Texture2D* LoadTexture2D(const std::string);
                bool DeleteTexture2D(unsigned int, GLuint);
        
                bool LoadTextFile(const std::string, std::string&);
                
                mugg::graphics::ShaderProgram* LoadShaderProgram();
                bool DeleteShaderProgram(unsigned int, GLuint);

                mugg::graphics::Shader* LoadShader(mugg::graphics::ShaderType, const std::string);
                bool DeleteShader(unsigned int, GLuint);
        };
    }
}

#endif
