#include "texture.hpp"

Texture::Texture(const char* filepath) {
    glGenTextures(1, &this->textureID);

    this->filepath = filepath;

    this->load();
}

Texture::~Texture() {
}

void Texture::load() {
    this->bind();

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

    if(this->image.loadFromFile(this->filepath)) {
		this->width = this->image.getSize().x;
    this->height = this->image.getSize().y;
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, this->width, this->height, 0, GL_RGBA, GL_UNSIGNED_BYTE, this->image.getPixelsPtr());
    } else {
        std::cerr << "Using fallback texture!\n";

        GLfloat pixels[] = {
            0.0f, 0.0f, 0.0f, 1.0f,   1.0f, 1.0f, 1.0f, 1.0f,
            1.0f, 1.0f, 1.0f, 1.0f,   0.0f, 0.0f, 0.0f, 1.0f
        };

        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 2, 2, 0, GL_RGBA, GL_FLOAT, pixels);
    }

    this->unbind();
}

void Texture::bind() {
    glBindTexture(GL_TEXTURE_2D, this->textureID);
}

void Texture::unbind() {
    glBindTexture(GL_TEXTURE_2D, 0);
}

int Texture::getWidth() {
    return this->width;
}

int Texture::getHeight() {
    return this->height;
}
