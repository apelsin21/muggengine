#include "shaderprogram.hpp"

mugg::ShaderProgram::ShaderProgram() {
    this->id = -1;
    this->linked = false;
}

mugg::ShaderProgram::~ShaderProgram() {
}

bool mugg::ShaderProgram::AddShader(std::string filepath, mugg::ShaderType type) {
    if(this->linked) {
        mugg::WriteToLog(mugg::INFO, "Adding shader to an already linked shader program!");
        return false;
    }

    mugg::Shader shader;
    shader.SetFilepath(filepath);
    shader.type = type;
    shader.id = 0;
    shader.compiled = false;

    this->shaders.push_back(shader);
    return true;
}

bool mugg::ShaderProgram::LoadShader(std::string filepath, mugg::ShaderType type, mugg::Shader &shader) {

    switch(type) {
        case mugg::VERTEX_SHADER:
            shader.id = glCreateShader(GL_VERTEX_SHADER);
            break;
        case mugg::FRAGMENT_SHADER:
            shader.id = glCreateShader(GL_FRAGMENT_SHADER);
            break;
        default:
            mugg::WriteToLog(mugg::ERROR, "Tried to load shader that isn't implemented yet");
            break;
    }

    std::string data = filehandler.ReadTextFromFilepath(filepath);

    if(data.size() == 0) {
        std::string error_msg("Failed to add shader at: ");
        error_msg += filepath;
        error_msg += " to shaderprogram, skipping. Reason: Empty file";
        mugg::WriteToLog(mugg::ERROR, error_msg);
        return false;
    }

    const char* tempData = data.c_str();
    glShaderSource(shader.id, 1, &tempData, NULL);

    shader.SetData(data);
    shader.type = type;

    return true;
}

bool mugg::ShaderProgram::CompileShader(mugg::Shader shader) {
    if(shader.GetData().size() == 0) {
        mugg::WriteToLog(mugg::ERROR, "Tried to compile empty shader!");
        return false;
    }

    glCompileShader(shader.id);

    GLint status = GL_FALSE;
    glGetShaderiv(shader.id, GL_COMPILE_STATUS, &status);
    if(status != GL_TRUE) {
        char* buffer = new char[512];
        glGetShaderInfoLog(shader.id, 512, NULL, buffer);
        std::string error_msg(buffer);
        mugg::WriteToLog(mugg::FATAL_ERROR, error_msg);
        shader.compiled = false;
        return false;
    }

    shader.compiled = true;

    return true;
}

bool mugg::ShaderProgram::LinkProgram() {
    if(this->shaders.size() == 0) {
        mugg::WriteToLog(mugg::ERROR, "Tried to link shaderless shaderprogram!");
        return false;
    }

    this->id = glCreateProgram();
    for(int i = 0; i <= this->shaders.size(); i++) {
        if(this->shaders[i].compiled) {
            glAttachShader(this->id, shaders[i].id);
        } else {
            this->CompileShader(this->shaders[i]);
        }
    }

    glLinkProgram(this->id);

    GLint status = GL_FALSE;
    glGetProgramiv(this->id, GL_LINK_STATUS, &status);
    if(status != GL_TRUE) {
        char* buffer = new char[512];
        glGetProgramInfoLog(this->id, 512, NULL, buffer);
        std::string error_msg(buffer);
        mugg::WriteToLog(mugg::FATAL_ERROR, error_msg);
        return false;
    }

    for(unsigned int i = 0; i <= this->shaders.size(); i++)
        glDeleteShader(this->shaders[i].id);

    return true;
}

bool mugg::ShaderProgram::LoadShadersFromDisk() {
    for(int i = 0; i <= this->shaders.size(); i++) {
        //if(!this->LoadShader(this->shaders[i].GetFilepath(), this->shaders[i].type, this->shaders[i])) {
        //    return false;
        //}
        if(!this->CompileShader(this->shaders[i])) {
            return false;
        }
    }

    return true;
}
