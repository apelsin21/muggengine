#ifndef MESH_HPP
#define MESH_HPP

#include "renderable.hpp"
#include "texture2d.hpp"

#include <GL/glew.h>

#include <assimp/Importer.hpp>

#include <vector>
#include <iostream>
#include <string>

namespace mugg {
    namespace graphics {
        class Mesh : public Renderable {
            private:
                std::vector<mugg::graphics::Texture2D> textureVector;
                std::string filepath;

                GLuint VBOID; //Vertex Buffer Object ID
                GLuint IBID; //Index Buffer ID
                unsigned int numberOfIndices;

                bool isLoaded;
            public:
                Mesh();
                ~Mesh();

                std::vector<mugg::graphics::Texture2D> GetTextureVector();
                mugg::graphics::Texture2D GetTextureByIndex(int);

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
