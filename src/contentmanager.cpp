#include "contentmanager.hpp"

mugg::core::ContentManager::~ContentManager() {
    std::cout << "Destructor called";
}

mugg::graphics::Texture2D* mugg::core::ContentManager::LoadTexture2D(const std::string filepath) {
    if(filepath == "") {
        std::cout << "Tried to load texture from empty string!\n";
        return new mugg::graphics::Texture2D(0);
    }

    GLuint id = 0;
    glGenTextures(1, &id);

    FREE_IMAGE_FORMAT format;
    FIBITMAP* bitmap = nullptr;

    mugg::graphics::Texture2D* texture = new mugg::graphics::Texture2D(id);
    
    format = FreeImage_GetFileType(filepath.c_str(), 0);

    if(!format || format == FIF_UNKNOWN) {
        std::cout << "Failed to load texture " << filepath << ", couldn't read the format. Corrupt or invalid bitmap.\n";
        texture->SetLoaded(false);
        return new mugg::graphics::Texture2D(0);
    }

    bitmap = FreeImage_Load(format, filepath.c_str());

    if(!bitmap) {
        std::cout << "Failed to load texture " << filepath << ", corrupt or invalid bitmap.\n";
        texture->SetLoaded(false);
        return new mugg::graphics::Texture2D(0);
    }

    bitmap = FreeImage_ConvertTo32Bits(bitmap);

    if(!bitmap) {
        std::cout << "FreeImage failed to convert texture " << filepath << " to 32 bits!\n";
        texture->SetLoaded(false);
        return new mugg::graphics::Texture2D(0);
    }

    texture->Bind();
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, FreeImage_GetWidth(bitmap), FreeImage_GetHeight(bitmap), 0, GL_BGRA, GL_UNSIGNED_BYTE, (GLvoid*)FreeImage_GetBits(bitmap));

    texture->SetFormat(format);
    texture->SetBitmap(bitmap);
    texture->SetFilepath(filepath);
    texture->SetLoaded(true);
    
    this->textures.push_back(id);
    texture->SetIndex(this->textures.size());

    return texture;
}

bool mugg::core::ContentManager::SearchForID(std::vector<GLuint>& idVector, GLuint id, int &out_index) {
    if(idVector.size() == 0 || id == 0) {
        return false;
    }

    std::sort(idVector.begin(), idVector.end());
    
    if(std::binary_search(idVector.begin(), idVector.end(), id)) {
        out_index = std::lower_bound(idVector.begin(), idVector.end(), id) - idVector.begin();
        return true;
    } else {
        return false;
    }
}

bool mugg::core::ContentManager::DeleteTexture2D(unsigned int index, GLuint id) {
    if(id == 0 || index == 0) {
        return false;
    }
    
    if(index < this->textures.size() && this->textures[index] == id) {
        if(glIsTexture(id) == GL_TRUE) {
            glDeleteTextures(1, &id);
        }
        this->textures.erase(this->textures.begin() + index);
     
        return true;
    } else {
        int index = 0;
    
        if(this->SearchForID(this->textures, id, index)) {
            this->textures.erase(this->textures.begin() + index);
            
            if(glIsTexture(id) == GL_TRUE) {
                glDeleteTextures(1, &id);
            }
            return true;
        }
    }

    return false;
}
