#ifndef TEXTURE_HPP
#define TEXTURE_HPP

#include <GL/glew.h>

#include <SFML/Graphics.hpp>

#include <iostream>

class Texture {
private:
    sf::Image image;
    GLuint textureID;
    const char* filepath;
    int width, height;

    void load();
public:
    Texture(const char* filepath);
    ~Texture();

    void bind();
    void unbind();

    int getWidth();
    int getHeight();
};

#endif // TEXTURE_HPP
