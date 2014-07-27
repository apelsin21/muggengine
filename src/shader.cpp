#include "shader.hpp"

mugg::graphics::Shader::Shader() : GLObject(nullptr) {
    this->type = mugg::graphics::ShaderType::VertexShader;
    this->ID = 0;
    this->filepath = "";
    this->data = "";
    this->loaded = false;
    this->compiledSuccessfully = false;
    this->hasGeneratedID = false;
}
mugg::graphics::Shader::Shader(mugg::core::ContentManager* creator) : GLObject(creator){
    this->type = mugg::graphics::ShaderType::VertexShader;
    this->ID = 0;
    this->filepath = "";
    this->data = "";
    this->loaded = false;
    this->compiledSuccessfully = false;
    this->hasGeneratedID = false;
}
mugg::graphics::Shader::~Shader() {
}

mugg::graphics::ShaderType mugg::graphics::Shader::GetType() {
    return this->type;
}
void mugg::graphics::Shader::SetType(mugg::graphics::ShaderType type) {
    this->type = type;
}

std::string mugg::graphics::Shader::GetFilepath() {
    return this->filepath;
}
void mugg::graphics::Shader::SetFilepath(std::string filepath) {
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
void mugg::graphics::Shader::SetData(const std::string& data) {
    this->loaded = true;
    this->data = data;
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

    this->compiledSuccessfully = true;
    return true;
}

void mugg::graphics::Shader::CheckForErrors() {
    GLint result = GL_FALSE;
    glGetShaderiv(this->ID, GL_COMPILE_STATUS, &result);

    this->compiledSuccessfully = (bool)result;
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

    this->hasGeneratedID = err;

    return true;
}
