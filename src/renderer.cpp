#include "renderer.hpp"

mugg::graphics::Renderer::Renderer() {
    this->backgroundColor.a = 1.0f;
}
mugg::graphics::Renderer::~Renderer() {
}

void mugg::graphics::Renderer::SetBackgroundColor(mugg::graphics::Color color) {
    this->backgroundColor.Set(color);
    glClearColor(this->backgroundColor.r, this->backgroundColor.g, this->backgroundColor.b, this->backgroundColor.a);
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

    glViewport(0, 0, viewportResolution.x, viewportResolution.y);
    
    if(this->programVector.size() != 0) {
        for(int i = 0; i <= this->programVector.size(); i++) {
            glUseProgram(this->programVector[i].GetProgramID());
        }
    }

    // Apply some transformations
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glTranslatef(0.f, 0.f, -200.f);
    glRotatef(2.0f * 0.05f, 1.f, 0.f, 0.f);
    glRotatef(2.0f * 0.03f, 0.f, 1.f, 0.f);
    glRotatef(2.0f * 0.09f, 0.f, 0.f, 1.f);

    // Draw a cube
    glBegin(GL_QUADS);

        glColor3f(1.f, 1.f, 0.f);
        glVertex3f(-50.f, -50.f, -50.f);
        glVertex3f(-50.f, 50.f, -50.f);
        glVertex3f( 50.f, 50.f, -50.f);
        glVertex3f( 50.f, -50.f, -50.f);

        glColor3f(1.f, 1.f, 0.f);
        glVertex3f(-50.f, -50.f, 50.f);
        glVertex3f(-50.f, 50.f, 50.f);
        glVertex3f( 50.f, 50.f, 50.f);
        glVertex3f( 50.f, -50.f, 50.f);

        glColor3f(0.f, 1.f, 1.f);
        glVertex3f(-50.f, -50.f, -50.f);
        glVertex3f(-50.f, 50.f, -50.f);
        glVertex3f(-50.f, 50.f, 50.f);
        glVertex3f(-50.f, -50.f, 50.f);

        glColor3f(0.f, 1.f, 1.f);
        glVertex3f(50.f, -50.f, -50.f);
        glVertex3f(50.f, 50.f, -50.f);
        glVertex3f(50.f, 50.f, 50.f);
        glVertex3f(50.f, -50.f, 50.f);

        glColor3f(1.f, 0.f, 1.f);
        glVertex3f(-50.f, -50.f, 50.f);
        glVertex3f(-50.f, -50.f, -50.f);
        glVertex3f( 50.f, -50.f, -50.f);
        glVertex3f( 50.f, -50.f, 50.f);

        glColor3f(1.f, 0.f, 1.f);
        glVertex3f(-50.f, 50.f, 50.f);
        glVertex3f(-50.f, 50.f, -50.f);
        glVertex3f( 50.f, 50.f, -50.f);
        glVertex3f( 50.f, 50.f, 50.f);

    glEnd();
}

void mugg::graphics::Renderer::EndRender() {
}
