#include "shaderprogram.hpp"

void mugg::ShaderProgram::AddShader(std::string filepath, mugg::ShaderType type) {
    if(this->linked) {
        mugg::WriteToLog(mugg::WARNING, "Tried to add shader to linked shader program!");
        return;
    }
    mugg::Shader shader = this->LoadShader(filepath, type);
    this->CompileShader(shader);
    this->shaders.push_back(shader);
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
}
