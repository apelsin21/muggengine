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
                GLuint positionBufferID, uvBufferID, colorBufferID, texID, vaoID;
                unsigned int maxSprites, spriteCount, positionCount, uvCount, colorCount;
                int stride;
                GLint posLocation, uvLocation, colLocation, modelLocation;
            
                GLfloat* vertexColorData, vertexPositionData, vertexUVData;
                
                virtual void UpdatePositions(unsigned int, const std::vector<float>&);
                virtual void UpdateUVs(unsigned int, const std::vector<float>&);
                virtual void UpdateColors(unsigned int, const std::vector<float>&);
            
                mugg::gui::GUIManager* parent;
            public:
                SpriteBatch(mugg::gui::GUIManager*, unsigned int, GLuint, GLint, GLint, GLint);
                ~SpriteBatch();
                
                virtual void AddSprite(mugg::gui::Sprite*);
                virtual void UpdateSprite(mugg::gui::Sprite*);
        
                virtual unsigned int GetSpriteCount();
                virtual unsigned int GetMaxSprites();
                
                virtual GLuint GetPositionBufferID();
                virtual GLuint GetUVBufferID();
                virtual GLuint GetColorBufferID();

                virtual GLuint GetTextureID();
                virtual void SetTextureID(GLuint);

                virtual void Render();
        };
    }
}

#endif
