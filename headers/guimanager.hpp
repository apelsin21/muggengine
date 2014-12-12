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
                
                mugg::graphics::Shader* vertexShader;
                mugg::graphics::Shader* fragmentShader;
                mugg::graphics::ShaderProgram* shaderProgram;
               
                std::string posAttribName, uvAttribName, modelAttribName, projectionMatrixUniformName;
                GLint posLocation, uvLocation, modelLocation, projectionMatrixUniformLocation;

                mugg::core::Engine* parent;

                glm::mat4 projectionMatrix;

                void UpdateSpriteBatches();
            public:
                GUIManager(mugg::core::Engine*);
                ~GUIManager();

                mugg::gui::Sprite* CreateSprite();
                void UpdateSprite(unsigned int);
                std::size_t GetNumberOfSprites();
                bool GetSpriteByIndex(int, mugg::gui::Sprite*&);

                mugg::gui::SpriteBatch* CreateSpriteBatch();

                mugg::graphics::ShaderProgram* GetShaderProgram();
                void SetShaderProgram(mugg::graphics::ShaderProgram*);

                glm::mat4 GetProjectionMatrix();
                void SetProjectionMatrix(const glm::mat4&);

                void Render();
        };
    }
}

#endif
