#ifndef MESH_HPP
#define MESH_HPP

#include "renderable.hpp"
#include "texture2d.hpp"
#include "color.hpp"

#include <GL/glew.h>
#include <glm/glm.hpp>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include <vector>
#include <iostream>
#include <string>

namespace mugg {
    namespace graphics {
        class Mesh : public Renderable {
            private:
                std::vector<mugg::graphics::Texture2D> diffuseTextures;
                std::vector<mugg::graphics::Texture2D> normalTextures;
                std::vector<mugg::graphics::Texture2D> specularTextures;
                
                std::vector<glm::vec4> vertices;
                std::vector<glm::vec2> uvs;
                std::vector<mugg::graphics::Color> colors;

                std::string filepath;

                GLuint VBOID; //Vertex Buffer Object ID
                GLuint IBID; //Index Buffer ID
                unsigned int numberOfIndices;

                bool loaded;

                void ProcessAssimpScene(const aiScene*);
                void Clear();
                void GenIDS();
            public:
                Mesh();
                ~Mesh();

                std::vector<mugg::graphics::Texture2D> GetDiffuseTextures();
                bool GetDiffuseTextureByIndex(int, mugg::graphics::Texture2D&);
                void AddDiffuseTexture(mugg::graphics::Texture2D);

                GLuint GetVBOID();
                void SetVBOID(GLuint VBOID);

                GLuint GetIBID();
                void SetIBID(GLuint IBID);
                
                std::string GetFilepath();

                bool Load(std::string);
        };
    }
}

#endif
