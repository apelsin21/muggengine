#include "contentmanager.hpp"

mugg::core::ContentManager::~ContentManager() {
    if(!this->textures.empty()) {
        for(unsigned int i = 0; i < this->textures.size(); i++) {
            this->DeleteTextureID(this->textures[i]);
        }
    }

    if(!this->shaders.empty()) {
        for(unsigned int i= 0; i < this->shaders.size(); i++) {
            this->DeleteShaderID(this->shaders[i]);
        }
    }

    if(!this->shaderPrograms.empty()) {
        for(unsigned int i = 0; i < this->shaders.size(); i++) {
            this->DeleteShaderProgramID(this->shaderPrograms[i]);
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

    if(format == FIF_UNKNOWN) {
        format = FreeImage_GetFIFFromFilename(filepath.c_str());
    }

    if(format == FIF_UNKNOWN) {
        std::cout << "Failed to read format of texture " << filepath << ", invalid image!\n";
        texture->SetLoaded(false);
        return texture;
    }

    if(FreeImage_FIFSupportsReading(format)) {
        bitmap = FreeImage_Load(format, filepath.c_str());
    } else {
        std::cout << "Texture " << filepath << " has a format unsupported by FreeImage!\n";
        texture->SetLoaded(false);
        return texture;
    }

    if(!bitmap) {
        std::cout << "Failed to load texture " << filepath << ", corrupt or invalid bitmap.\n";
        texture->SetLoaded(false);
        return texture;
    }

    FIBITMAP* temp = bitmap;
    temp = FreeImage_ConvertTo32Bits(bitmap);
    FreeImage_Unload(temp);

    if(!bitmap) {
        std::cout << "FreeImage failed to convert texture " << filepath << " to 32 bit colour!\n";
        texture->SetLoaded(false);
        return texture;
    }

    texture->Bind();

    texture->SetWrap(texture->GetUWrap(), texture->GetVWrap());

    texture->SetFilter(texture->GetMinFilter(), texture->GetMagFilter());

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, FreeImage_GetWidth(bitmap), FreeImage_GetHeight(bitmap), 0, GL_BGRA, GL_UNSIGNED_BYTE, (GLvoid*)FreeImage_GetBits(bitmap));

    texture->SetWidth(FreeImage_GetWidth(bitmap));
    texture->SetHeight(FreeImage_GetHeight(bitmap));
    texture->SetColorsUsed(FreeImage_GetColorsUsed(bitmap));
    texture->SetBPP(FreeImage_GetBPP(bitmap));
    texture->SetFilepath(filepath);
    texture->SetLoaded(true);

    FreeImage_Unload(bitmap);
    
    texture->SetIndex(this->textures.size());
    this->textures.push_back(id);

    return texture;
}
bool mugg::core::ContentManager::DeleteTexture2D(unsigned int index, GLuint id) {
    if(id == 0 || this->textures.empty()) {
        return false;
    }

    if(index < this->textures.size() && this->textures[index] == id) {
        this->textures.erase(this->textures.begin() + index);
        std::cout << "Deleted texture2D with id: " << id << " and index: " << index << " on the first try!\n";
        this->DeleteTextureID(id);

        return true;
    } else {
        int index = 0;
    
        if(this->SearchForID(this->textures, id, index)) {
            this->textures.erase(this->textures.begin() + index);
            std::cout << "Deleted texture2D with id: " << id << " and index: " << index << " on the second try!\n";

            this->DeleteTextureID(id);

            return true;
        }
    }

    return false;
}
void mugg::core::ContentManager::DeleteTextureID(GLuint id) {
    if(glIsTexture(id) == GL_TRUE) {
        std::cout << "Actually deleted texture " << id << std::endl;
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

    shader->SetIndex(this->shaders.size());
    this->shaders.push_back(id);

    return shader;
}
bool mugg::core::ContentManager::DeleteShader(unsigned int index, GLuint id) {
    if(id == 0) {
        return false;
    }
    
    if(index < this->shaders.size() && this->shaders[index] == id) {
        this->DeleteShaderID(id);
        std::cout << "Deleting shader with id: " << id << " and index " << index << ", first try!\n";
        this->shaders.erase(this->shaders.begin() + index);
     
        return true;
    } else {
        int index = 0;
    
        if(this->SearchForID(this->shaders, id, index)) {
            this->shaders.erase(this->shaders.begin() + index);
            std::cout << "Deleting shader with id: " << id << " and index " << index << ", second try!\n";
           
            this->DeleteShaderID(id);

            return true;
        }
    }

    return false;
}
void mugg::core::ContentManager::DeleteShaderID(GLuint id) {
    if(glIsShader(id) == GL_TRUE) {
        std::cout << "Actually deleted shader " << id << "\n";
        glDeleteShader(id);
    }
}

bool mugg::core::ContentManager::SearchForID(std::vector<GLuint>& idVector, GLuint id, int &out_index) {
    if(idVector.empty() || id == 0) {
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

mugg::graphics::ShaderProgram* mugg::core::ContentManager::LoadShaderProgram() {
    GLuint id = glCreateProgram();

    mugg::graphics::ShaderProgram* program = new mugg::graphics::ShaderProgram(id);

    program->SetIndex(this->shaderPrograms.size());
    this->shaderPrograms.push_back(id);

    return program;
}
bool mugg::core::ContentManager::DeleteShaderProgram(unsigned int index, GLuint id) {
    if(id == 0) {
        return false;
    }

    if(index < this->shaderPrograms.size() && this->shaderPrograms[index] == id) {
        this->DeleteShaderProgramID(id);
        std::cout << "Deleting shaderprogram with id: " << id << " and index " << index << ", first try!\n";
        this->shaderPrograms.erase(this->shaderPrograms.begin() + index);
     
        return true;
    } else {
        int index = 0;
    
        if(this->SearchForID(this->shaderPrograms, id, index)) {
            this->shaderPrograms.erase(this->shaderPrograms.begin() + index);
            std::cout << "Deleting shaderprogram with id: " << id << " and index " << index << ", first try!\n";
           
            this->DeleteShaderProgramID(id);

            return true;
        }
    }

    std::cout << "Failed to delete shaderprogram with id: " << id << " and index: " << index << std::endl;

    return false;
}
void mugg::core::ContentManager::DeleteShaderProgramID(GLuint id) {
    if(glIsProgram(id) == GL_TRUE) {
        std::cout << "Actually deleted shaderprogram " << id << "\n";
        glDeleteProgram(id);
    }
}
