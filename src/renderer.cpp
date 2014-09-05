#include "renderer.hpp"

mugg::graphics::Renderer::Renderer(mugg::core::Engine* p) {
    this->parent = p;
    this->wireframe = false;
    this->deltatime = 0;
    this->frametime = 0;
    this->frames = 0;
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
    this->lastTime = std::chrono::system_clock::now();
   
    glEnable(GL_DEPTH_TEST);
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

double mugg::graphics::Renderer::GetDeltatime() {
    return this->deltatime;
}
double mugg::graphics::Renderer::GetFrametime() {
    return this->frametime;
}
double mugg::graphics::Renderer::GetFPS() {
    if(this->frametime != 0)
        return 1000.0/this->frametime;
    else
        return 0;
}

void mugg::graphics::Renderer::UpdateTime() {
    this->frames++;

    this->deltatime = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now() - this->lastTime).count();

    if(this->deltatime >= 1000.0) {
        if(this->frames != 0)
            this->frametime = 1000.0/this->frames;
        this->frames = 0;
        this->lastTime = std::chrono::system_clock::now();
    }
}

void mugg::graphics::Renderer::Render() {
    this->UpdateTime();

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    if(this->programVector.size() != 0) {
        for(int i = 0; i < this->programVector.size(); i++) {
            glUseProgram(this->programVector[i]);
        }
    }
}
