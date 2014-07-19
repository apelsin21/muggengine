#include "texture2d.hpp"

mugg::graphics::Texture2D::Texture2D() {
    this->width = 0;
    this->height = 0;
    this->bpp = 0;
    this->ID = 0;
    this->colorsUsed = 0;

    this->bitmap = nullptr;
    this->format = FIF_UNKNOWN;

    this->loaded = false;
    this->mipMaps = false;
    this->hasGeneratedID = false;
    
    this->GenID();
}
mugg::graphics::Texture2D::Texture2D(std::string filepath) {
    this->width = 0;
    this->height = 0;
    this->bpp = 0;
    this->ID = 0;
    this->colorsUsed = 0;

    this->bitmap = nullptr;
    this->format = FIF_UNKNOWN;

    this->loaded = false;
    this->mipMaps = false;
    this->hasGeneratedID = false;
    
    this->GenID();
    this->Load(filepath);
}
mugg::graphics::Texture2D::~Texture2D() {
    if(hasGeneratedID)
        glDeleteTextures(1, &this->ID);
}

bool mugg::graphics::Texture2D::Load(std::string filepath) {
    return this->Load(filepath, mugg::graphics::TextureRepeatPattern::Repeat, mugg::graphics::TextureFilter::Linear, false);
}

bool mugg::graphics::Texture2D::Load(std::string filepath, mugg::graphics::TextureRepeatPattern pattern, mugg::graphics::TextureFilter filter, bool mipMaps) {
    this->format = FreeImage_GetFileType(filepath.c_str(), 0);
    
    if(!this->format) {
        std::cout << "Failed to get format of " << filepath << ", corrupt or invalid image!\n";
        this->loaded = false;
        return false;
    }
    
    this->bitmap = FreeImage_Load(this->format, filepath.c_str());

    if(!this->bitmap) {
        std::cout << "Failed to load image " << filepath << ", corrupt or invalid image!\n";
        this->loaded = false;
        return false;
    }

    this->bitmap = FreeImage_ConvertTo32Bits(this->bitmap);
    
    this->Bind();

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, FreeImage_GetWidth(this->bitmap), FreeImage_GetHeight(this->bitmap), 0, GL_BGRA, GL_UNSIGNED_BYTE, (GLvoid*)FreeImage_GetBits(this->bitmap));

    GLenum error = glGetError();
    if(error) {
        std::cout << "There was an error sending the texture to OpenGL!\n";
        this->loaded = false;
        return false;
    }

    switch(pattern) {
        case mugg::graphics::TextureRepeatPattern::Repeat:
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
            break;
        default:
            std::cout << "Used texture repeat pattern for " << filepath << " isn't implemented yet!\n";
            this->loaded = false;
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
            this->loaded = false;
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
    this->mipMaps = mipMaps;
   
    FreeImage_Unload(this->bitmap);

    this->loaded = true;
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
std::string mugg::graphics::Texture2D::GetFilepath() {
    return this->filepath;
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
