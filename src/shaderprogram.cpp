#include "shaderprogram.hpp"

mugg::graphics::ShaderProgram::ShaderProgram() : GLObject(nullptr) {
    this->linked = false;
    this->compiledSuccessfully = false;
    this->hasGeneratedID = false;
}
mugg::graphics::ShaderProgram::ShaderProgram(mugg::core::ContentManager* creator) : GLObject(creator) {
    this->linked = false;
    this->compiledSuccessfully = false;
    this->hasGeneratedID = true;
}

mugg::graphics::ShaderProgram::~ShaderProgram() {
}

bool mugg::graphics::ShaderProgram::HasGeneratedID() {
    return this->hasGeneratedID;
}

bool mugg::graphics::ShaderProgram::AddShader(GLuint shader) {
    if(!glIsShader(shader)) {
        std::cout << "Tried adding an unvalid shader to shaderprogram!\n";
        return false;
    }

    this->shaders.push_back(shader);
    
    return true;
}

bool mugg::graphics::ShaderProgram::GetCompiledSuccessfully() {
    return this->compiledSuccessfully;
}

bool mugg::graphics::ShaderProgram::Link() {
    if(this->shaders.size() != 0) {
        for(unsigned int i = 0; i < this->shaders.size(); i++) {
            glAttachShader(this->ID, this->shaders[i]);
        }
    } else {
        std::cout << "Tried to link shaderless shaderprogram!\n";
        this->compiledSuccessfully = false;
        return false;
    }
    
    glLinkProgram(this->ID);
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

    for(unsigned int i = 0; i <= logLength; i++) {
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
