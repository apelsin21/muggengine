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

                void FillBuffers();
                void GenIDS();

                mugg::core::ContentManager* parent;
            public:
                Mesh(mugg::core::ContentManager*);
                ~Mesh();

                virtual mugg::graphics::Texture2D* GetTexture();
                virtual void SetTexture(mugg::graphics::Texture2D*);

                virtual void SetIndices(const std::vector<unsigned short>&);
                virtual int GetNumberOfIndices();

                virtual void SetVertices(const std::vector<glm::vec3>&);
                virtual int GetNumberOfVertices();
                
                virtual void SetUVS(const std::vector<glm::vec2>&);
                virtual int GetNumberOfUVS();
                
                virtual void SetNormals(const std::vector<glm::vec3>&);
                virtual int GetNumberOfNormals();

                virtual GLuint GetVAOID();
                virtual void SetVAOID(GLuint);
                
                virtual GLuint GetPositionBufferID();
                virtual void SetPositionBufferID(GLuint);
                
                virtual GLuint GetUVBufferID();
                virtual void SetUVBufferID(GLuint);
                
                virtual GLuint GetNormalBufferID();
                virtual void SetNormalBufferID(GLuint);
                
                virtual GLuint GetElementBufferID();
                virtual void SetElementBufferID(GLuint);
                
                virtual std::string GetFilepath();
                virtual void SetFilepath(const std::string&);
                
                virtual void Clear();
        };
    }
}

#endif
