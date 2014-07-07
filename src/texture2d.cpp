#include "texture2d.hpp"

mugg::graphics::Texture2D::Texture2D() {
    this->width = 0;
    this->height = 0;
    this->bpp = -1;
    this->ID = 0;
    this->colorsUsed = -1;
    this->bitmap = nullptr;
    this->filepath = "";

    this->loaded = false;
    this->hasGeneratedID = false;
}
mugg::graphics::Texture2D::~Texture2D() {
    if(hasGeneratedID)
        glDeleteTextures(1, &this->ID);

    FreeImage_Unload(this->bitmap);
}

bool mugg::graphics::Texture2D::LoadFromFile(const char* filepath, mugg::graphics::TextureRepeatPattern pattern, mugg::graphics::TextureFilter filter, bool mipMaps) {
    if(!this->hasGeneratedID) {
        if(!this->GenID()) {
            std::cout << "Failed to generate an OpenGL texture ID!\n";
            return false;
        }
    }
    
    this->format = FreeImage_GetFileType(filepath, 0);
    
    if(!this->format) {
        std::cout << "Failed to get format of " << filepath << ", corrupt or invalid image!\n";
        return false;
    }
    
    this->bitmap = FreeImage_Load(this->format, filepath);

    if(!this->bitmap) {
        std::cout << "Failed to load image " << filepath << ", corrupt or invalid image!\n";
        return false;
    }

    this->Bind();
    
    switch(pattern) {
        case mugg::graphics::TextureRepeatPattern::Repeat:
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
            break;
        default:
            std::cout << "Used texture repeat pattern for " << filepath << " isn't implemented yet!\n";
            return false;
            break;
    }

    switch(filter) {
        case mugg::graphics::TextureFilter::Nearest:
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
            break;
        case mugg::graphics::TextureFilter::Linear:
            if(mipMaps) {
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
                glGenerateMipmap(GL_TEXTURE_2D);
            } else {
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            }
            break;
        default:
            std::cout << "Used texture filter for " << filepath << " isn't implemented yet!\n";
            return false;
            break;
    }

    this->width = FreeImage_GetWidth(this->bitmap);
    this->height = FreeImage_GetHeight(this->bitmap);
    this->bpp = FreeImage_GetBPP(this->bitmap);
    this->colorsUsed = FreeImage_GetColorsUsed(this->bitmap);
    this->filepath = filepath;
    this->filter = filter;
    this->pattern = pattern;
    this->loaded = true;
    this->mipMaps = mipMaps;
    return true;
}

int mugg::graphics::Texture2D::GetWidth() {
    return this->width;
}
int mugg::graphics::Texture2D::GetHeight() {
    return this->height;
}
int mugg::graphics::Texture2D::GetBPP() {
    return this->bpp;
}
int mugg::graphics::Texture2D::GetColorsUsed() {
    return this->colorsUsed;
}
const char* mugg::graphics::Texture2D::GetFilepath() {
    return this->filepath;
}
GLuint mugg::graphics::Texture2D::GetID() {
    return this->ID;
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

mugg::graphics::TextureRepeatPattern mugg::graphics::Texture2D::GetPattern() {
    return this->pattern;
}
mugg::graphics::TextureFilter mugg::graphics::Texture2D::GetFilter() {
    return this->filter;
}

bool mugg::graphics::Texture2D::GenID() {
    glGenTextures(1, &this->ID);
    
    if(glIsTexture(this->ID) == GL_TRUE) {
        this->hasGeneratedID = true;
        return true;
    } else {
        this->hasGeneratedID = false;
        return false;
    }
}

void mugg::graphics::Texture2D::Bind() {
    glBindTexture(GL_TEXTURE_2D, this->ID);
}
void mugg::graphics::Texture2D::UnBind() {
    glBindTexture(GL_TEXTURE_2D, 0);
}
