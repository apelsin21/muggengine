#ifndef SPRITEBATCH_HPP
#define SPRITEBATCH_HPP

#include <iostream>
#include <string>
#include <vector>

#include <GL/glew.h>

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace mugg {
    namespace gui {
        class Sprite;
        class GUIManager;
    
        class SpriteBatch {
            private:
                GLuint  vboID, texID, vaoID;
                unsigned int maxSprites, spriteCount, positionsCount, uvsCount, colorsCount;
                int stride, bufferSize;
                GLint posLocation, uvLocation, colLocation, modelLocation;
            
                GLfloat* vertexColorData, vertexPositionData, vertexUVData;
                
                virtual void UpdatePositions(const std::vector<float>&);
                virtual void UpdateUVs(const std::vector<float>&);
                virtual void UpdateColors(const std::vector<float>&);
            
                mugg::gui::GUIManager* parent;
            public:
                SpriteBatch(mugg::gui::GUIManager*, unsigned int, GLuint, GLint, GLint, GLint);
                ~SpriteBatch();

                virtual int GetCurrentBufferOffset();
                
                virtual void AddSprite(mugg::gui::Sprite*);
        
                virtual unsigned int GetSpriteCount();
                virtual unsigned int GetMaxSprites();
                
                virtual GLuint GetVBOID();
                virtual GLuint GetTextureID();
                
                virtual void SetTextureID(GLuint);

                virtual void Render();
        };
    }
}

#endif
