#include "renderer.hpp"

mugg::graphics::Renderer::Renderer() {
}
mugg::graphics::Renderer::~Renderer() {
}

void mugg::graphics::Renderer::SetBackgroundColor(const mugg::graphics::Color& color) {
    this->backgroundColor = color;
    glClearColor(this->backgroundColor.r, this->backgroundColor.g, this->backgroundColor.b, this->backgroundColor.a);
}
mugg::graphics::Color mugg::graphics::Renderer::GetBackgroundColor() {
    return this->backgroundColor;
}

bool mugg::graphics::Renderer::AddShaderProgram(std::shared_ptr<mugg::graphics::ShaderProgram>& shaderProgram) {
    if(shaderProgram->GetCompiledSuccessfully()) {
        this->programVector.push_back(shaderProgram);
        return true;
    }
    
    std::cout << "Tried to add a shaderprogram with errors!\n";
    
    return false;
}
std::shared_ptr<mugg::graphics::ShaderProgram> mugg::graphics::Renderer::GetShaderProgramByIndex(int index) {
    if(this->programVector.size() != 0) {
        return this->programVector[index];
    }
}
std::vector<std::shared_ptr<mugg::graphics::ShaderProgram>> mugg::graphics::Renderer::GetShaderProgramVector() {
    return this->programVector;
}

bool mugg::graphics::Renderer::Initialize() {
}

void mugg::graphics::Renderer::Draw() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    if(this->programVector.size() != 0) {
        for(int i = 0; i < this->programVector.size(); i++) {
            glUseProgram(this->programVector[i]->GetID());
        }
    }
}
