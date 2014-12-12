#ifndef MESH_HPP
#define MESH_HPP

#include "texture2d.hpp"
#include "color.hpp"

#include <GL/glew.h>
#include <glm/glm.hpp>

#include <vector>
#include <iostream>
#include <string>

namespace mugg {
    namespace core {
        class ContentManager;
    }
    
    namespace graphics {
        class Mesh {
            private:
                mugg::graphics::Texture2D* texture;

                std::vector<unsigned short> indices;
                std::vector<glm::vec3> vertices;
                std::vector<glm::vec2> uvs;
                std::vector<glm::vec3> normals;

                std::string filepath;

                GLuint vaoID, positionBufferID, uvBufferID, normalBufferID, elementBufferID;

                bool loaded;

                void GenIDS();

                mugg::core::ContentManager* parent;
            public:
                Mesh(mugg::core::ContentManager*);
                ~Mesh();

                mugg::graphics::Texture2D* GetTexture();
                void SetTexture(mugg::graphics::Texture2D*);

                void SetIndices(const std::vector<unsigned short>&);
                std::vector<unsigned short> GetIndices();
                int GetNumberOfIndices();

                void SetVertices(const std::vector<glm::vec3>&);
                std::vector<glm::vec3> GetVertices();
                int GetNumberOfVertices();
                
                void SetUVS(const std::vector<glm::vec2>&);
                std::vector<glm::vec2> GetUVS();
                int GetNumberOfUVS();
                
                void SetNormals(const std::vector<glm::vec3>&);
                std::vector<glm::vec3> GetNormals();
                int GetNumberOfNormals();

                GLuint GetVAOID();
                void SetVAOID(GLuint);
                
                GLuint GetPositionBufferID();
                void SetPositionBufferID(GLuint);
                
                GLuint GetUVBufferID();
                void SetUVBufferID(GLuint);
                
                GLuint GetNormalBufferID();
                void SetNormalBufferID(GLuint);
                
                GLuint GetElementBufferID();
                void SetElementBufferID(GLuint);
                
                std::string GetFilepath();
                void SetFilepath(const std::string&);
                
                void Clear();
        };
    }
}

#endif
