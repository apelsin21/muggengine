#ifndef GUIMANAGER_HPP
#define GUIMANAGER_HPP

#include <iostream>
#include <vector>
#include <vector>

#include <GL/glew.h>

#include "graphicsdefs.hpp"
#include "image.hpp"

namespace mugg {
    namespace gui {
        class GUIManager {
            private:
                std::vector<unsigned int> indices;
                std::vector<glm::vec3> vertices;
                std::vector<glm::vec2> uvs;

                std::vector<mugg::gui::Image> images;

                GLuint IBID;
                GLuint VBOID;
                GLuint VAOID;
            public:
                GUIManager();
                ~GUIManager();

                void SetImageAtIndex(int, mugg::gui::Image);
                mugg::gui::Image GetImageByIndex(int);
                std::vector<mugg::gui::Image> GetImages();
        
                void AddImage(mugg::gui::Image);
                void CreateImageFromFile(std::string filepath);
        
                void Render();
        };
    }
}

#endif
