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
                
                std::vector<mugg::gui::SpriteBatch*> spriteBatches;
                    
                GLuint vaoID, positionBufferID, uvBufferID;
                GLuint vsID, fsID, programID;
               
                GLint posLocation, uvLocation, modelLocation, projectionMatrixUniformLocation;

                mugg::core::Engine* parent;

                glm::mat4 projectionMatrix;

                void UpdateSpriteBatches();
            public:
                GUIManager(mugg::core::Engine*);
                ~GUIManager();

                virtual mugg::gui::Sprite* CreateSprite();
                virtual void UpdateSprite(unsigned int);
                virtual std::size_t GetNumberOfSprites();
                virtual bool GetSpriteByIndex(int, mugg::gui::Sprite*&);

                virtual mugg::gui::SpriteBatch* CreateSpriteBatch();

                virtual GLuint GetShaderProgramID();
                virtual void SetShaderProgramID(GLuint);

                virtual glm::mat4 GetProjectionMatrix();
                virtual void SetProjectionMatrix(const glm::mat4&);

                virtual void Render();
        };
    }
}

#endif
