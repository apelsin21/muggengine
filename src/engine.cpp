#include "engine.hpp"

mugg::Engine::Engine(mugg::Context context) {
    this->context = context;
}

mugg::Engine::~Engine() {
}

bool mugg::Engine::Initialize() {
    mugg::WriteToLog(mugg::INFO, "#### Engine instance initializing! ####");
    
    if(!this->context.GetIsEnabled()) {
        if(!this->context.Enable()) {
            mugg::WriteToLog(mugg::FATAL_ERROR, "Engine instance got unenabled context, failed trying to enable it!");
            return false;
        }
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, this->context.GetMajorVersion());
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, this->context.GetMinorVersion());

    if(this->context.GetFlags().size() <= 0) {
        mugg::WriteToLog(mugg::ERROR, "Tried to enable context, failed, no context flags!");
        return false;
    }

    for(int i = 0; i <= this->shaderPrograms.size(); i++) {
        if(!this->shaderPrograms[i].LoadShadersFromDisk()) {
            mugg::WriteToLog(mugg::ERROR, "Couldn't load shaders from disk for shaderprogram!");
            return false;
        }
        if(!this->shaderPrograms[i].LinkProgram()) {
            mugg::WriteToLog(mugg::ERROR, "Couldn't link shaderprogram!");
            return false;
        }
    }

    return true;
}

void mugg::Engine::AddShaderProgram(mugg::ShaderProgram program) {
    this->shaderPrograms.push_back(program);
}
std::vector<mugg::ShaderProgram> mugg::Engine::GetShaderPrograms() {
    return this->shaderPrograms;
}

void mugg::Engine::Render() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}
