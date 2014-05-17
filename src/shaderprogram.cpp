#include "shaderprogram.hpp"

mugg::ShaderProgram::ShaderProgram() {
    this->id = -1;
    this->linked = false;
}

mugg::ShaderProgram::~ShaderProgram() {
}

bool mugg::ShaderProgram::AddShader(std::string filepath, mugg::ShaderType type) {
    if(this->linked) {
        mugg::WriteToLog(mugg::WARNING, "Tried to add shader to an already linked shader program!");
        return false;
    }

    mugg::Shader shader;
    if(this->LoadShader(filepath, type, shader) == false) {
        return false;
    }

    if(!this->CompileShader(shader)) {
        mugg::WriteToLog(mugg::ERROR, "Failed to compile shader");
        return false;
    }

    this->shaders.push_back(shader);
    return true;
}

bool mugg::ShaderProgram::LoadShader(std::string filepath, mugg::ShaderType type, mugg::Shader &outShader) {
    mugg::Shader shader;

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

    const char* data = filehandler.ReadTextFromFilepath(filepath).c_str();

    if(data == nullptr || strcmp(data, "") > 0) {
        std::string error_msg("Failed to add shader at: ");
        error_msg += filepath;
        error_msg += " to shaderprogram, skipping";
        mugg::WriteToLog(mugg::ERROR, error_msg);
        return false;
    }

    glShaderSource(shader.id, 1, &data, NULL);

    shader.SetData(filehandler.ReadDataFromFilepath(filepath));
    shader.type = type;

    return true;
}

bool mugg::ShaderProgram::CompileShader(mugg::Shader shader) {
    glCompileShader(shader.id);

    GLint status = GL_FALSE;
    glGetShaderiv(shader.id, GL_COMPILE_STATUS, &status);
    if(status != GL_TRUE) {
        char* buffer = new char[512];
        glGetShaderInfoLog(shader.id, 512, NULL, buffer);
        std::string error_msg(buffer);
        mugg::WriteToLog(mugg::FATAL_ERROR, error_msg);
        return false;
    }

    return true;
}

bool mugg::ShaderProgram::LinkProgram() {
    if(this->shaders.size() <= 0) {
        mugg::WriteToLog(mugg::ERROR, "Tried to link shaderless shaderprogram!");
        return false;
    }

    this->id = glCreateProgram();
    for(int i = 0; i <= this->shaders.size(); i++)
        glAttachShader(this->id, shaders[i].id);

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

    glUseProgram(this->id);

    for(unsigned int i = 0; i <= this->shaders.size(); i++)
        glDeleteShader(this->shaders[i].id);

    return true;
}

bool mugg::ShaderProgram::LoadShadersFromDisk() {
    for(int i = 0; i <= this->shaders.size(); i++) {
            this->LoadShader()
    }

    return true;
}
