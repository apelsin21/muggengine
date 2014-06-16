#ifndef TEXTURE_HPP
#define TEXTURE_HPP

#include <GL/glew.h>
#include <SFML/Graphics.hpp>
#include <glm/glm.hpp>
#include <iostream>

namespace mugg {
    namespace graphics {
        static GLfloat fallbackTexture[] = {
            0.0f, 0.0f, 0.0f, 1.0f,     1.0f, 1.0f, 1.0f, 1.0f,

            1.0f, 1.0f, 1.0f, 1.0f,     0.0f, 0.0f, 0.0f, 1.0f,
        };

        class Texture2D {
            private:
                sf::Image image;
                GLuint textureID;
                glm::vec2 resolution;
                const char* filepath;
                GLenum magFilter, minFilter;
                GLenum wrapS, wrapT;
            public:
                Texture2D(GLenum magFilter, GLenum minFilter, GLenum wrapS, GLenum wrapT);
                ~Texture2D();

                bool LoadFromFilepath(const char* filepath);

                void Bind();
                void UnBind();

                const char* GetFilepath();

                glm::vec2 GetResolution();
        };
    }
}

#endif
