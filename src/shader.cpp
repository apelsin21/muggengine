#include "shader.hpp"

mugg::graphics::Shader::Shader() {
    this->type = mugg::graphics::ShaderType::VertexShader;
    this->ID = 0;
    this->filepath = "";
    this->data = "";
    this->loaded = false;
    this->compiledSuccessfully = false;
}
mugg::graphics::Shader::Shader(mugg::graphics::ShaderType type, const char* filepath) {
    this->type = type;
    this->filepath = filepath;
    this->data = "";
    this->compiledSuccessfully = false;
    this->loaded = false;

    this->GenID();
    this->SetType(type);
    this->LoadFromFilepath(filepath);
    this->Compile();
    
    this->CheckForErrors();
    
    if(!this->compiledSuccessfully)
        std::cout << this->GetLog() << std::endl;
}
mugg::graphics::Shader::~Shader() {
}

void mugg::graphics::Shader::GenID() {
    switch(this->type) {
        case VertexShader:
            this->ID = glCreateShader(GL_VERTEX_SHADER);
            break;
        case FragmentShader:
            this->ID = glCreateShader(GL_FRAGMENT_SHADER);
            break;
        case GeometryShader:
            this->ID = glCreateShader(GL_GEOMETRY_SHADER);
            break;
    }

    this->hasGeneratedID = true;
}

GLuint mugg::graphics::Shader::GetID() {
    return this->ID;
}
void mugg::graphics::Shader::DeleteID() {
    if(this->hasGeneratedID) {
        glDeleteShader(this->ID);
        this->hasGeneratedID = false;
    }
}

mugg::graphics::ShaderType mugg::graphics::Shader::GetType() {
    return this->type;
}
void mugg::graphics::Shader::SetType(mugg::graphics::ShaderType type) {
    this->type = type;
}

const char* mugg::graphics::Shader::GetFilepath() {
    return this->filepath;
}
void mugg::graphics::Shader::SetFilepath(const char* filepath) {
    this->filepath = filepath;
}

bool mugg::graphics::Shader::GetLoaded() {
    return this->loaded;
}

bool mugg::graphics::Shader::GetCompiledSuccessfully() {
    return this->compiledSuccessfully;
}

std::string mugg::graphics::Shader::GetData() {
    return this->data;
}
void mugg::graphics::Shader::SetData(std::string data) {
    this->loaded = true;
    this->data = data;
}

bool mugg::graphics::Shader::LoadFromFilepath(const char* filepath) {
    if(filepath == "") {
        std::cout << "Tried to load shader from empty string!\n";
        this->loaded = false;
        return false;
    }

    this->filepath = filepath;

    if(!mugg::io::LoadTextFromFile(filepath, this->data)) {
        std::cout << "Failed to load shader from filepath: " << filepath << std::endl;
        this->loaded = false;
        return false;
    }

    this->loaded = true;

    return true;
}

bool mugg::graphics::Shader::Compile() {
    if(!this->Validate()) {
        std::cout << "Tried to compile unvalid OpenGL shader!\n";
        this->compiledSuccessfully = false;
        return false;
    }

    const char* tempData = this->data.c_str();
    glShaderSource(this->ID, 1, &tempData, NULL);
    glCompileShader(this->ID);

    this->CheckForErrors();

    if(!this->compiledSuccessfully) {
        std::cout << this->GetLog() << std::endl;
        return false;
    }

    return true;
}

void mugg::graphics::Shader::CheckForErrors() {
    GLint result = GL_FALSE;
    glGetShaderiv(this->ID, GL_COMPILE_STATUS, &result);

    this->compiledSuccessfully = result;
}

const char* mugg::graphics::Shader::GetLog() {
    GLint logLength = 0;
    glGetShaderiv(this->ID, GL_INFO_LOG_LENGTH, &logLength);

    GLchar buffer[logLength];
    glGetShaderInfoLog(this->ID, logLength, NULL, buffer);
    
    std::string returnval;

    for(int i = 0; i <= logLength; i++) {
        returnval += buffer[i];
    }

    return returnval.c_str();
}

bool mugg::graphics::Shader::Validate() {
    GLboolean err = glIsShader(this->ID);

    if(err == GL_FALSE) {
        return false;
    }
    
    return true;
}
