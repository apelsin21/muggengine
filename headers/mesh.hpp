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
#include <assert.h>
#include <iostream>
#include <string>
#include <memory>

namespace mugg {
    namespace graphics {
        class Mesh : public Renderable {
            private:
                std::vector<std::shared_ptr<mugg::graphics::Texture2D>> textures;

                std::vector<glm::vec3> vertices;
                std::vector<glm::vec2> uvs;
                std::vector<glm::vec3> normals;

                std::string filepath;

                GLuint VBOID; //Vertex Buffer Object ID
                GLuint IBID; //Index Buffer ID
                
                unsigned int numberOfIndices;
                std::vector<unsigned int> materialIndices;
                std::vector<unsigned int> indices;

                bool loaded;

                void ProcessAssimpScene(const aiScene*);
                void ProcessAssimpMesh(unsigned int, const aiMesh*);
                void ProcessAssimpMaterials(const aiScene*);
                
                void FillBuffers();
                void Clear();
                void GenIDS();
            public:
                Mesh();
                ~Mesh();

                std::vector<std::shared_ptr<mugg::graphics::Texture2D>> GetTextures();
                bool GetTextureByIndex(int, std::shared_ptr<mugg::graphics::Texture2D>&);
                void AddTexture(std::shared_ptr<mugg::graphics::Texture2D>&);

                int GetNumberOfTextures();
                int GetNumberOfVertices();
                int GetNumberOfIndices();
                int GetNumberOfUVS();
                int GetNumberOfNormals();

                GLuint GetVBOID();
                void SetVBOID(GLuint VBOID);

                GLuint GetIBID();
                void SetIBID(GLuint IBID);
                
                std::string GetFilepath();
        };
    }
}

#endif
