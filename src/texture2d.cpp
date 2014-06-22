#include "texture2d.hpp"

mugg::graphics::Texture2D::Texture2D(GLenum magFilter, GLenum minFilter, GLenum wrapS, GLenum wrapT) {
    glGenTextures(1, &this->ID);
    this->filepath = "";
    this->magFilter = magFilter;
    this->minFilter = minFilter;
    this->wrapS = wrapS;
    this->wrapT = wrapT;
}
mugg::graphics::Texture2D::Texture2D(const char* filepath) {
    glGenTextures(1, &this->ID);

    this->filepath = filepath;
    this->magFilter = GL_NEAREST;
    this->minFilter = GL_NEAREST;
    this->wrapS = GL_REPEAT;
    this->wrapT = GL_REPEAT;

    this->LoadFromFilepath(filepath);
}

mugg::graphics::Texture2D::~Texture2D() {
    glDeleteTextures(1, &this->ID);
}

bool mugg::graphics::Texture2D::LoadFromFilepath(const char* filepath) {
    this->Bind();

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, this->wrapS);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, this->wrapT);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, this->magFilter);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, this->minFilter);

    if(this->image.loadFromFile(filepath)) {
        this->resolution.x = this->image.getSize().x;
        this->resolution.y = this->image.getSize().y;

        this->filepath = filepath;

        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, this->resolution.x, this->resolution.y, 0, GL_RGBA, GL_UNSIGNED_BYTE, this->image.getPixelsPtr());
    } else {
        std::cout << "Using default fallback texture!\n";

        this->resolution.x = 2;
        this->resolution.y = 2;

        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 2, 2, 0, GL_RGBA, GL_FLOAT, mugg::graphics::fallbackTexture);
        
        return false;
    }

    this->UnBind();

    return true;
}

void mugg::graphics::Texture2D::Bind() {
    glBindTexture(GL_TEXTURE_2D, this->ID);
}

void mugg::graphics::Texture2D::UnBind() {
    glBindTexture(GL_TEXTURE_2D, 0);
}

const char* mugg::graphics::Texture2D::GetFilepath() {
    return this->filepath;
}

glm::vec2 mugg::graphics::Texture2D::GetResolution() {
    return this->resolution;
}
