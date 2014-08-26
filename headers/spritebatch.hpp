#ifndef SPRITEBATCH_HPP
#define SPRITEBATCH_HPP

#include <iostream>
#include <string>
#include <vector>

#include <GL/glew.h>

#include <glm/glm.hpp>

namespace mugg {
    namespace graphics {
        class SpriteBatch {
            private:
                GLuint positionBuffer, uvBuffer, colorBuffer, modelMatrixBuffer, texID, vaoID;
                unsigned int maxSprites, spriteCount;
                GLint posLocation, uvLocation, colLocation, modelLocation;
            public:
                SpriteBatch(unsigned int, GLuint, GLint, GLint, GLint, GLint);
                ~SpriteBatch();
                
                virtual void Add();
                virtual void UpdatePosition(unsigned int, const glm::vec2&);
                virtual void UpdateUV(unsigned int, const glm::vec2&);
                virtual void UpdateColor(unsigned int, const glm::vec3&);
                virtual void UpdateModelMatrix(unsigned int, const glm::mat4&);
        
                virtual unsigned int GetSpriteCount();
                virtual unsigned int GetMaxSprites();
                
                virtual GLuint GetPositionBuffer();
                virtual GLuint GetUVBuffer();
                virtual GLuint GetColorBuffer();
                virtual GLuint GetModelMatrixBuffer();

                virtual GLuint GetTexture();
        
                virtual void Render();
        };
    }
}

#endif
