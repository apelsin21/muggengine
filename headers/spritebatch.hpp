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
    namespace graphics {
        class SpriteBatch {
            private:
                GLuint positionBufferID, uvBufferID, colorBufferID, texID, vaoID;
                unsigned int maxSprites, spriteCount, positionCount, uvCount, colorCount;
                int stride;
                GLint posLocation, uvLocation, colLocation, modelLocation;
            public:
                SpriteBatch(unsigned int, GLuint, GLint, GLint, GLint);
                ~SpriteBatch();
                
                virtual void Add();
                virtual void UpdatePosition(unsigned int, const glm::vec3&);
                virtual void UpdateUV(unsigned int, const glm::vec2&);
                virtual void UpdateColor(unsigned int, const glm::vec3&);
                virtual void UpdateSprite(unsigned int, const glm::mat4&);
        
                virtual unsigned int GetSpriteCount();
                virtual unsigned int GetMaxSprites();
                
                virtual GLuint GetPositionBufferID();
                virtual GLuint GetUVBufferID();
                virtual GLuint GetColorBufferID();

                virtual GLuint GetTextureID();
        
                virtual void Render();
        };
    }
}

#endif
