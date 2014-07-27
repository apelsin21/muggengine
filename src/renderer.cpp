#include "renderer.hpp"

mugg::graphics::Renderer::Renderer() {
    this->wireframe = false;
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

bool mugg::graphics::Renderer::AddShaderProgram(GLuint shaderProgram) {
    if(glIsProgram(shaderProgram) == GL_TRUE) {
        this->programVector.push_back(shaderProgram);
        return true;
    }

    std::cout << "Tried adding unlinked shaderprogram to renderer!\n";

    return false;
}
GLuint mugg::graphics::Renderer::GetShaderProgramByIndex(int index) {
    if(this->programVector.size() != 0) {
        return this->programVector[index];
    }
}
std::vector<GLuint> mugg::graphics::Renderer::GetShaderProgramVector() {
    return this->programVector;
}

bool mugg::graphics::Renderer::Initialize() {
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void mugg::graphics::Renderer::SetWireframe(bool wireframe) {
    this->wireframe = wireframe;

    if(this->wireframe) {
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    } else {
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    }
}
bool mugg::graphics::Renderer::GetWireframe() {
    return this->wireframe;
}

void mugg::graphics::Renderer::Draw() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    if(this->programVector.size() != 0) {
        for(int i = 0; i < this->programVector.size(); i++) {
            glUseProgram(this->programVector[i]);
        }
    }
}
