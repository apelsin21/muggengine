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

namespace mugg {
    namespace core {
        enum LoadableType {
            Texture2D,
            Mesh,
            Shader
        };
        static const char* LoadableTypeString[] = {
            "Texture2D",
            "Mesh",
            "Shader",
            "NULL"
        };

        class ContentManager {
            private:
                std::ifstream in_stream;
                std::ofstream out_stream;
           
                std::vector<GLuint> textures;

                void ProcessAssimpScene(const aiScene*);
                void ProcessAssimpMesh(unsigned int, const aiMesh*);
                void ProcessAssimpMaterials(const aiScene*);

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
        };
    }
}

#endif
