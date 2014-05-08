#include "shaderprogram.hpp"

void mugg::ShaderProgram::AddShader(std::string filepath, mugg::ShaderType type) {
    if(this->linked) {
        mugg::WriteToLog(mugg::WARNING, "Tried to add shader to linked shader program!");
        return;
    }
    mugg::Shader shader = this->LoadShader(filepath, type);
    if(this->CompileShader(shader))
        this->shaders.push_back(shader);
    else
        return;
}

mugg::Shader mugg::ShaderProgram::LoadShader(std::string filepath, mugg::ShaderType type) {
    mugg::Shader shader;

    switch(type) {
        case mugg::VERTEX_SHADER:
            shader.id = glCreateShader(GL_VERTEX_SHADER);
            break;
        case mugg::FRAGMENT_SHADER:
            shader.id = glCreateShader(GL_FRAGMENT_SHADER);
            break;
        default:
            mugg::WriteToLog(mugg::ERROR, "FIX THIS, TRIED TO LOAD GEOMETRY SHADER, DON'T KNOW HOW PLS FIX");
            //TODO: Learn how geometry shaders work, fix urgently
            break;
    }

    shader.SetData(filehandler.ReadDataFromFilepath(filepath));

    const char* data = new char[shader.GetSize()];
    data = &shader.GetData()[0];

    glShaderSource(shader.id, 1, &data, NULL);
    delete data;
}

bool mugg::ShaderProgram::CompileShader(mugg::Shader shader) {
    glCompileShader(shader.id);

    GLint status;
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
    this->id = glCreateProgram();
    for(int i = 0; i <= this->shaders.size(); i++)
        glAttachShader(this->id, shaders[i].id);

    glLinkProgram(this->id);

    glUseProgram(this->id);
}
