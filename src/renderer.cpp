#include "renderer.hpp"

mugg::graphics::Renderer::Renderer() {
    this->backgroundColor.a = 1.0f;
}
mugg::graphics::Renderer::~Renderer() {
    for(int i = 0; i < this->programVector.size(); i++) {
        if(this->programVector[i].HasGeneratedID()) {
            this->programVector[i].DeleteID();
        }
    }
}

void mugg::graphics::Renderer::SetBackgroundColor(mugg::graphics::Color color) {
    this->backgroundColor.Set(color);
    glClearColor(this->backgroundColor.r, this->backgroundColor.g, this->backgroundColor.b, this->backgroundColor.a);
}
mugg::graphics::Color mugg::graphics::Renderer::GetBackgroundColor() {
    return this->backgroundColor;
}

bool mugg::graphics::Renderer::AddShaderProgram(mugg::graphics::ShaderProgram shaderProgram) {
    if(shaderProgram.GetCompiledSuccessfully()) {
        this->programVector.push_back(shaderProgram);
        return true;
    }
    
    std::cout << "Tried to add a shaderprogram with errors!\n";
    
    return false;
}
mugg::graphics::ShaderProgram mugg::graphics::Renderer::GetShaderProgramByIndex(int index) {
    if(this->programVector.size() != 0) {
        return this->programVector[index];
    }
}
std::vector<mugg::graphics::ShaderProgram> mugg::graphics::Renderer::GetShaderProgramVector() {
    return this->programVector;
}

bool mugg::graphics::Renderer::Initialize() {
}

void mugg::graphics::Renderer::Render(mugg::Window window) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    int width, height;
    window.GetFramebufferSize(width, height);

    if(width != this->fbWidth && height != this->fbHeight) {
        this->fbWidth = width;
        this->fbHeight = height;
        glViewport(0, 0, this->fbWidth, this->fbHeight);
    }
    
    if(this->programVector.size() != 0) {
        for(int i = 0; i < this->programVector.size(); i++) {
            glUseProgram(this->programVector[i].GetID());
        }
    }
}

void mugg::graphics::Renderer::Render(int width, int height) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    if(width != this->fbWidth && height != this->fbHeight) {
        this->fbWidth = width;
        this->fbHeight = height;
        glViewport(0, 0, this->fbWidth, this->fbHeight);
    }
    
    if(this->programVector.size() != 0) {
        for(int i = 0; i < this->programVector.size(); i++) {
            glUseProgram(this->programVector[i].GetID());
        }
    }
}
