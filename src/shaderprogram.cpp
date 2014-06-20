#include "shaderprogram.hpp"

mugg::graphics::ShaderProgram::ShaderProgram() {
    this->linked = false;
    this->compiledSuccessfully = false;
}

mugg::graphics::ShaderProgram::~ShaderProgram() {
    this->DeleteID();
}

void mugg::graphics::ShaderProgram::DeleteID() {
    if(this->hasGeneratedID)
        glDeleteProgram(this->ID);

    this->hasGeneratedID = false;
}
GLuint mugg::graphics::ShaderProgram::GetID() {
    return this->ID;
}
bool mugg::graphics::ShaderProgram::HasGeneratedID() {
    return this->hasGeneratedID;
}

bool mugg::graphics::ShaderProgram::AddShader(Shader shader) {
    if(!shader.GetCompiledSuccessfully() && !shader.GetLoaded()) {
        std::cout << "Tried to add a shader with errors to shaderprogram!\n";
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
        std::cout << this->GetCompileLog() << std::endl;
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

const char* mugg::graphics::ShaderProgram::GetCompileLog() {
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

