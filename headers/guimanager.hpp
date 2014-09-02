#ifndef GUIMANAGER_HPP
#define GUIMANAGER_HPP

#include <vector>
#include <iostream>
#include <string>

#include <GL/glew.h>

#define GLM_FORCE_RADIANS
#define GLM_FORCE_CXX11
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "shaderprogram.hpp"
#include "shader.hpp"

#include "spritebatch.hpp"

#include "fileutils.hpp"

namespace mugg {
    namespace core {
        class Engine;
    }
    
    namespace gui {
        class Image;
        
        class GUIManager {
            private:
                std::vector<mugg::gui::Image*> images;
                std::vector<unsigned int> imagesToBeUpdated;
                
                std::vector<mugg::graphics::SpriteBatch*> spriteBatches;
                    
                GLuint vaoID;
                GLuint vsID, fsID, programID;
               
                GLint posLocation, uvLocation, colLocation, modelMatrixUniformLocation;

                mugg::core::Engine* parent;
            public:
                GUIManager(mugg::core::Engine*);
                ~GUIManager();

                virtual mugg::gui::Image* CreateImage();
                virtual void UpdateImage(unsigned int);
                virtual std::size_t GetNumberOfImages();
                virtual bool GetImageByIndex(int, mugg::gui::Image*&);

                virtual void Render();
        };
    }
}

#endif
