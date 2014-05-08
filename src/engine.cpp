#include "engine.hpp"

mugg::Engine::Engine(mugg::Context context) {
    this->context = context;
    this->backgroundColor.r = 0.0f;
    this->backgroundColor.g = 0.0f;
    this->backgroundColor.b = 0.0f;
    this->backgroundColor.a = 1.0f;
}

void mugg::Engine::Initialize() {
    this->SetBackgroundColor(this->color);
    
    glewExperimental = GL_TRUE;
    if(glewInit() != GLEW_OK) {
    	mugg::WriteToLog(mugg::FATAL_ERROR, "Failed to initialize GLEW!");
        return -1;
    }

    glEnable(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

}

void mugg::Engine::SetBackgroundColor(mugg::Color color) {
    glClearColor(color.r, color.g, color.b, color.a);
}
mugg::Color mugg::Engine::GetBackgroundColor() {
    return this->color;
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
