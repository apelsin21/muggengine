#include "engine.hpp"

mugg::Engine::Engine(mugg::Context context) {
    this->context = context;
}

mugg::Engine::~Engine() {
}

bool mugg::Engine::Initialize() {
    if(!this->context.GetIsEnabled()) {
        std::string error_msg;
        error_msg += "Tried to initialize Engine instance without enabling the used context";
        error_msg += " in a proper way.";
        mugg::WriteToLog(mugg::ERROR, error_msg);
    }

    if(!this->context.Enable() && this->context.GetFlags().size() == NULL) {
        mugg::WriteToLog(mugg::ERROR, "Tried to enable context, failed, no context flags");
        return false;
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
