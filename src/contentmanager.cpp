#include "contentmanager.hpp"

mugg::core::ContentManager::~ContentManager() {
    if(this->textures.size() != 0) {
        for(unsigned int i = 0; i <= this->textures.size(); i++) {
            if(glIsTexture(this->textures[i]) == GL_TRUE) {
                glDeleteTextures(1, &this->textures[i]);
            }
        }
    }

    if(this->shaders.size() != 0) {
        for(unsigned int i= 0; i <= this->shaders.size(); i++) {
            if(glIsShader(this->shaders[i]) == GL_TRUE) {
                glDeleteShader(this->shaders[i]);
            }
        }
    }
}

mugg::graphics::Texture2D* mugg::core::ContentManager::LoadTexture2D(const std::string filepath) {
    if(filepath == "") {
        std::cout << "Tried to load texture from empty string!\n";
        return nullptr;
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
        return texture;
    }

    bitmap = FreeImage_Load(format, filepath.c_str());

    if(!bitmap) {
        std::cout << "Failed to load texture " << filepath << ", corrupt or invalid bitmap.\n";
        texture->SetLoaded(false);
        return texture;
    }

    bitmap = FreeImage_ConvertTo32Bits(bitmap);

    if(!bitmap) {
        std::cout << "FreeImage failed to convert texture " << filepath << " to 32 bits!\n";
        texture->SetLoaded(false);
        return texture;
    }

    texture->Bind();
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, FreeImage_GetWidth(bitmap), FreeImage_GetHeight(bitmap), 0, GL_BGRA, GL_UNSIGNED_BYTE, (GLvoid*)FreeImage_GetBits(bitmap));

    texture->SetWidth(FreeImage_GetWidth(bitmap));
    texture->SetHeight(FreeImage_GetHeight(bitmap));
    texture->SetColorsUsed(FreeImage_GetColorsUsed(bitmap));
    texture->SetBPP(FreeImage_GetBPP(bitmap));
    texture->SetFilepath(filepath);
    texture->SetLoaded(true);

    FreeImage_Unload(bitmap);
    
    this->textures.push_back(id);
    texture->SetIndex(this->textures.size());

    return texture;
}
bool mugg::core::ContentManager::DeleteTexture2D(unsigned int index, GLuint id) {
    if(id == 0 || index == 0) {
        return false;
    }
    
    if(index < this->textures.size() && this->textures[index] == id) {
        this->DeleteTextureID(id);

        this->textures.erase(this->textures.begin() + index);
     
        return true;
    } else {
        int index = 0;
    
        if(this->SearchForID(this->textures, id, index)) {
            this->textures.erase(this->textures.begin() + index);
            
            this->DeleteTextureID(id);

            return true;
        }
    }

    return false;
}
void mugg::core::ContentManager::DeleteTextureID(GLuint id) {
    if(glIsTexture(id) == GL_TRUE) {
        glDeleteTextures(1, &id);
    }
} 

mugg::graphics::Shader* mugg::core::ContentManager::LoadShader(mugg::graphics::ShaderType type, const std::string filepath) {
    if(filepath == "") {
        std::cout << "Tried loading shader from empty path!\n";
        return new mugg::graphics::Shader(0);
    }

    GLuint id = glCreateShader(mugg::graphics::ShaderTypeToGLEnum(type));
    
    mugg::graphics::Shader* shader = new mugg::graphics::Shader(id);

    shader->SetType(type);
    shader->SetFilepath(filepath);

    std::string data;

    if(!this->LoadTextFile(filepath, data)) {
        std::cout << "Failed to load shader data from " << filepath << std::endl;
        return new mugg::graphics::Shader(0);
    }

    shader->SetData(data);
    
    if(!shader->Compile()) {
        std::cout << "Shader " << filepath << " failed to compile!\n";
        return new mugg::graphics::Shader(0);
    }

    this->shaders.push_back(id);
    shader->SetIndex(this->shaders.size());

    return shader;
}
bool mugg::core::ContentManager::DeleteShader(unsigned int index, GLuint id) {
    if(id == 0 || index == 0) {
        return false;
    }
    
    if(index < this->shaders.size() && this->shaders[index] == id) {
        this->DeleteShaderID(id);
        this->shaders.erase(this->shaders.begin() + index);
     
        return true;
    } else {
        int index = 0;
    
        if(this->SearchForID(this->shaders, id, index)) {
            this->shaders.erase(this->shaders.begin() + index);
           
            this->DeleteShaderID(id);

            return true;
        }
    }

    return false;
}
void mugg::core::ContentManager::DeleteShaderID(GLuint id) {
    if(glIsShader(id) == GL_TRUE) {
        glDeleteShader(id);
    }
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
bool mugg::core::ContentManager::LoadTextFile(const std::string filepath, std::string &out_data) {
    std::string data;
    
    if(filepath == "") {
        std::cout << "Failed to load text file because of empty path!\n";
        return false;
    }

    this->inStream.open(filepath, std::ios::in);

    if(this->inStream.is_open()) {
        std::string line;

        while(std::getline(this->inStream, line)) {
            data += "\n" + line;
        }

        this->inStream.close();
    } else {
        std::cout << "Failed to open " << filepath << " for reading!\n";
        return false;
    }

    out_data = data;

    return true;
}
