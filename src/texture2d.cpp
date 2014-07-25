#include "texture2d.hpp"

mugg::graphics::Texture2D::Texture2D(GLuint id) {
    this->width = 0;
    this->height = 0;
    this->bpp = 0;
    this->ID = id;
    this->colorsUsed = 0;
    this->index = 0;

    this->bitmap = nullptr;
    this->format = FIF_UNKNOWN;

    this->loaded = false;
    this->mipMaps = false;
    this->hasGeneratedID = false;
}
mugg::graphics::Texture2D::~Texture2D() {
}

FREE_IMAGE_FORMAT mugg::graphics::Texture2D::GetFormat() {
    return this->format;
}
void mugg::graphics::Texture2D::SetFormat(const FREE_IMAGE_FORMAT& format) {
    this->format = format;
}

FIBITMAP* mugg::graphics::Texture2D::GetBitmap() {
    return this->bitmap;
}
void mugg::graphics::Texture2D::SetBitmap(FIBITMAP* bitmap) {
    this->bitmap = bitmap;
    
    this->width = FreeImage_GetWidth(this->bitmap);
    this->height = FreeImage_GetHeight(this->bitmap);
    this->bpp = FreeImage_GetBPP(this->bitmap);
    this->colorsUsed = FreeImage_GetColorsUsed(this->bitmap);

    FreeImage_Unload(this->bitmap);
}

void mugg::graphics::Texture2D::SetWidth(int width) {
    this->width = width;
}
int mugg::graphics::Texture2D::GetWidth() {
    return this->width;
}

void mugg::graphics::Texture2D::SetHeight(int height) {
    this->height = height;
}
int mugg::graphics::Texture2D::GetHeight() {
    return this->height;
}

void mugg::graphics::Texture2D::SetBPP(int bpp) {
    this->bpp = bpp;
}
int mugg::graphics::Texture2D::GetBPP() {
    return this->bpp;
}

void mugg::graphics::Texture2D::SetColorsUsed(int colorsUsed) {
    this->colorsUsed = colorsUsed;
}
int mugg::graphics::Texture2D::GetColorsUsed() {
    return this->colorsUsed;
}

void mugg::graphics::Texture2D::SetFilepath(std::string filepath) {
    this->filepath = filepath;
}
std::string mugg::graphics::Texture2D::GetFilepath() {
    return this->filepath;
}

void mugg::graphics::Texture2D::SetLoaded(bool loaded) {
    this->loaded = loaded;
}
bool mugg::graphics::Texture2D::IsLoaded() {
    return this->loaded;
}

bool mugg::graphics::Texture2D::HasGeneratedID() {
    return this->hasGeneratedID;
}
bool mugg::graphics::Texture2D::UsesMipMaps() {
    return this->mipMaps;
}

mugg::graphics::TextureWrap mugg::graphics::Texture2D::GetUWrap() {
    return this->uWrap;
}
mugg::graphics::TextureWrap mugg::graphics::Texture2D::GetVWrap() {
    return this->vWrap;
}
void mugg::graphics::Texture2D::SetWrap(TextureWrap u, TextureWrap v) {
    this->uWrap = u;
    this->vWrap = v;
    this->Bind();
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, TextureWrapToGLEnum(u));
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, TextureWrapToGLEnum(v));
}

mugg::graphics::TextureFilter mugg::graphics::Texture2D::GetMinFilter() {
    return this->minFilter;
}
mugg::graphics::TextureFilter mugg::graphics::Texture2D::GetMagFilter() {
    return this->magFilter;
}
void mugg::graphics::Texture2D::SetTextureFilter(TextureFilter minFilter, TextureFilter magFilter) {
    this->minFilter = minFilter;
    this->magFilter = magFilter;
    this->Bind();
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, TextureFilterToGLEnum(minFilter));
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, TextureFilterToGLEnum(magFilter));
}

void mugg::graphics::Texture2D::Bind() {
    glBindTexture(GL_TEXTURE_2D, this->ID);
}
void mugg::graphics::Texture2D::UnBind() {
    glBindTexture(GL_TEXTURE_2D, 0);
}
