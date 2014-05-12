#include "engine.hpp"

mugg::Engine::Engine(mugg::Context context) {
    this->context = context;
}

mugg::Engine::~Engine() {
}

bool mugg::Engine::Initialize() {
    glewExperimental = GL_TRUE;
    if(glewInit() != GLEW_OK) {
    	mugg::WriteToLog(mugg::FATAL_ERROR, "Failed to initialize GLEW!");
    	return false;
    }

    glEnable(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    return false;
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
