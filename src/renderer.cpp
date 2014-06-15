#include "renderer.hpp"

mugg::graphics::Renderer::Renderer() {
    this->backgroundColor.a = 1.0f;

    glewExperimental = GL_TRUE;
    if(glewInit() != GLEW_OK) {
        std::cout << "GLEW failed to initialize!\n";
    }
}
mugg::graphics::Renderer::~Renderer() {
}

void mugg::graphics::Renderer::SetBackgroundColor(mugg::graphics::Color backgroundcolor) {
    this->backgroundColor = backgroundColor;
}
mugg::graphics::Color mugg::graphics::Renderer::GetBackgroundColor() {
    return this->backgroundColor;
}

void mugg::graphics::Renderer::AddShaderProgram(mugg::core::ShaderProgram shaderProgram) {
    this->programVector.push_back(shaderProgram);
}
mugg::core::ShaderProgram mugg::graphics::Renderer::GetShaderProgramByIndex(int index) {
    if(this->programVector.size() != 0) {
        return this->programVector[index];
    }
}
std::vector<mugg::core::ShaderProgram> mugg::graphics::Renderer::GetShaderProgramVector() {
    return this->programVector;
}

bool mugg::graphics::Renderer::Initialize() {
    glEnable(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_BLEND | GL_DEPTH_TEST);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glDepthFunc(GL_ADD);
}

void mugg::graphics::Renderer::BeginRender(glm::vec2 viewportResolution = glm::vec2(800, 600)) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(this->backgroundColor.r, this->backgroundColor.g, this->backgroundColor.b, this->backgroundColor.a);

    glViewport(0, 0, viewportResolution.x, viewportResolution.y);
}

void mugg::graphics::Renderer::EndRender() {
}
