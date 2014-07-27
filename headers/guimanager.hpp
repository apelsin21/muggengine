#ifndef GUIMANAGER_HPP
#define GUIMANAGER_HPP

#include <vector>
#include <iostream>
#include <string>

#include <GL/glew.h>

#include <glm/glm.hpp>

namespace mugg {
    namespace gui {
        class GUIManager {
            private:
                std::vector<GLuint> textures;
        
                GLuint vboID, vaoID;
            public:
                GUIManager();
                ~GUIManager();

                void AddTexture2D(GLuint);
                GLuint GetTexture2D(unsigned int);
                void RemoveTexture2D(unsigned int);

                void Render();
        };
    }
}

#endif
