#include "shaderprogram.hpp"

mugg::graphics::ShaderProgram::ShaderProgram() {
    this->linked = false;
    this->compiledSuccessfully = false;
    this->hasGeneratedID = false;
}

mugg::graphics::ShaderProgram::~ShaderProgram() {
}

void mugg::graphics::ShaderProgram::DeleteID() {
    if(this->hasGeneratedID)
        glDeleteProgram(this->ID);

    this->hasGeneratedID = false;
}
bool mugg::graphics::ShaderProgram::HasGeneratedID() {
    return this->hasGeneratedID;
}

bool mugg::graphics::ShaderProgram::AddShader(Shader shader) {
    if(!shader.GetCompiledSuccessfully()) {
        std::cout << "Tried to add a uncompiled shader to shaderprogram!\n";
        return false;
    }

    this->shaderVector.push_back(shader);

    return true;
}

bool mugg::graphics::ShaderProgram::AddShader(mugg::graphics::ShaderType type, const char* filepath) {
    mugg::graphics::Shader shader;

    shader.SetType(type);
    shader.GenID();
    shader.SetFilepath(filepath);

    std::string data;
    
    if(!mugg::io::LoadTextFromFile(filepath, data)) {
        std::cout << "Failed to load shader from path: " << filepath << std::endl;
        return false;
    }

    shader.SetData(data);

    if(!shader.Compile()) {
        return false;
    }

    this->shaderVector.push_back(shader);

    return true;
}

bool mugg::graphics::ShaderProgram::GetCompiledSuccessfully() {
    return this->compiledSuccessfully;
}

bool mugg::graphics::ShaderProgram::Link() {
    this->ID = glCreateProgram();
    this->hasGeneratedID = true;

    if(this->shaderVector.size() != 0) {
        for(int i = 0; i < this->shaderVector.size(); i++) {
            glAttachShader(this->ID, shaderVector[i].GetID());
        }
    } else {
        std::cout << "Tried to link shaderless shaderprogram!\n";
        this->compiledSuccessfully = false;
        return false;
    }

    glLinkProgram(this->ID);
    
    for(int i = 0; i < this->shaderVector.size(); i++)
        this->shaderVector[i].DeleteID();
    
    this->CheckForErrors();

    if(!this->compiledSuccessfully) {
        this->linked = false;
        std::cout << this->GetLog() << std::endl;
        return false;
    }

    this->compiledSuccessfully = true;
    this->linked = true;

    return true;
}

void mugg::graphics::ShaderProgram::CheckForErrors() {
    GLint result = GL_FALSE;

    glGetProgramiv(this->ID, GL_LINK_STATUS, &result);

    if(result == GL_FALSE) {
        this->compiledSuccessfully = false;
    }

    this->compiledSuccessfully = true;
}

const char* mugg::graphics::ShaderProgram::GetLog() {
    int logLength = 0;
    glGetProgramiv(this->ID, GL_INFO_LOG_LENGTH, &logLength);
    
    GLchar buffer[logLength];
    glGetProgramInfoLog(this->ID, logLength, NULL, buffer);

    std::string returnval;

    for(int i = 0; i <= logLength; i++) {
        returnval += buffer[i];
    }

    return returnval.c_str();
}

bool mugg::graphics::ShaderProgram::Validate() {
    int result = GL_FALSE;

    glGetProgramiv(this->ID, GL_VALIDATE_STATUS, &result);

    if(result == GL_FALSE) {
        std::cout << "Validation log: " << this->GetLog() << std::endl;

        return false;
    }

    return true;
}

GLint mugg::graphics::ShaderProgram::GetNumberOfAttachedShaders() {
    GLint numberOfShaders = 0;

    glGetProgramiv(this->ID, GL_ATTACHED_SHADERS, &numberOfShaders);

    return numberOfShaders;
}
