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
                GLuint modelMatrixBuffer, texID;
                unsigned int maxSprites, spriteCount;
            public:
                SpriteBatch(unsigned int);
                ~SpriteBatch();
                
                virtual void Add(const glm::mat4&);
                virtual void Replace(unsigned int, const glm::mat4&);
                virtual void Delete(unsigned int);
        
                virtual unsigned int GetSpriteCount();
                virtual unsigned int GetMaxSprites();
                virtual GLuint GetModelMatrixBuffer();

                virtual GLuint GetTexture();
        };
    }
}

#endif
