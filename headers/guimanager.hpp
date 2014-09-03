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
        class Sprite;
        
        class GUIManager {
            private:
                std::vector<mugg::gui::Sprite*> sprites;
                std::vector<unsigned int> spritesToBeUpdated;
                
                std::vector<mugg::graphics::SpriteBatch*> spriteBatches;
                    
                GLuint vaoID;
                GLuint vsID, fsID, programID;
               
                GLint posLocation, uvLocation, colLocation, modelMatrixUniformLocation;

                glm::mat4 modelMatrix;

                mugg::core::Engine* parent;

                void UpdateSpriteBatches();
            public:
                GUIManager(mugg::core::Engine*);
                ~GUIManager();

                virtual mugg::gui::Sprite* CreateSprite();
                virtual void UpdateSprite(unsigned int);
                virtual std::size_t GetNumberOfSprites();
                virtual bool GetSpriteByIndex(int, mugg::gui::Sprite*&);

                virtual glm::mat4 GetModelMatrix();
                virtual void SetModelMatrix(const glm::mat4&);

                virtual void Render();
        };
    }
}

#endif
