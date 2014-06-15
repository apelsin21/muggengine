#include "shaderprogram.hpp"

mugg::core::ShaderProgram::ShaderProgram(const char* vsFilepath, const char* fsFilepath) {
    this->programID = glCreateProgram();
    this->vsID = glCreateShader(GL_VERTEX_SHADER);
    this->fsID = glCreateShader(GL_FRAGMENT_SHADER);
    
    this->linked = false;

    if(!this->AddShaders(vsFilepath, fsFilepath)) {
        std::cout << "Failed to load vertex shader " << vsFilepath << " and fragment shader " << fsFilepath << std::endl;
    }

}

mugg::core::ShaderProgram::~ShaderProgram() {
    glDeleteProgram(this->programID);
}

bool mugg::core::ShaderProgram::AddShaders(const char* vsFilepath, const char* fsFilepath) {
    if(!mugg::io::LoadTextFromFile(vsFilepath, this->vsData)) {
        std::cout << "Failed to load vertex shader " << vsFilepath << " from disk.\n";
        return false;
    }
    if(!mugg::io::LoadTextFromFile(fsFilepath, this->fsData)) {
        std::cout << "Failed to load fragment shader " << fsFilepath << " from disk.\n";
        return false;
    }

    return true;
}

void mugg::core::ShaderProgram::CompileShader(GLuint shaderID, const char* data) {
    glShaderSource(shaderID, 1, &data, NULL);
    glCompileShader(shaderID); 
}

bool mugg::core::ShaderProgram::CheckShaderForError(GLuint shaderID) {
    GLint result = GL_FALSE;
    int logLength = 0;

    glGetShaderiv(shaderID, GL_COMPILE_STATUS, &result);
    glGetShaderiv(shaderID, GL_INFO_LOG_LENGTH, &logLength);

    if(result == GL_FALSE) {
        GLchar buffer[logLength];
        glGetShaderInfoLog(shaderID, logLength, NULL, buffer);
        std::cout << buffer << std::endl;

        return false;
    }

    return true;
}

bool mugg::core::ShaderProgram::Link() {    
    this->CompileShader(this->vsID, this->vsData.c_str());
    if(!this->CheckShaderForError(this->vsID)) {
        std::cout << "Vertex Shader has errors!\n";
        return false;
    }
    
    this->CompileShader(this->fsID, this->fsData.c_str());
    if(!this->CheckShaderForError(this->fsID)) {
        std::cout << "Fragment Shader has errors!\n";
        return false;
    }

    glAttachShader(this->programID, this->vsID);
    glAttachShader(this->programID, this->fsID);

    glLinkProgram(this->programID);
    
    glDeleteShader(this->vsID);
    glDeleteShader(this->fsID);

    if(!this->CheckProgramForError()) {
        return false;
    }

    return true;
}

bool mugg::core::ShaderProgram::CheckProgramForError() {
    GLint result = GL_FALSE;
    int logLength = 0;

    glGetProgramiv(this->programID, GL_LINK_STATUS, &result);
    glGetProgramiv(this->programID, GL_INFO_LOG_LENGTH, &logLength);

    if(result == GL_FALSE) {
        GLchar buffer[logLength];
        glGetProgramInfoLog(this->programID, logLength, NULL, buffer);
        std::cout << buffer << std::endl;

        return false;
    }

    return true;
}


