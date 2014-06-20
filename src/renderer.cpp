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

void mugg::graphics::Renderer::BeginRender(glm::vec2 viewportResolution = glm::vec2(800, 600)) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    if(viewportResolution != this->viewportResolution) {
        this->viewportResolution = viewportResolution;
        glViewport(0, 0, viewportResolution.x, viewportResolution.y);
    }
    
    if(this->programVector.size() != 0) {
        for(int i = 0; i < this->programVector.size(); i++) {
            glUseProgram(this->programVector[i].GetID());

            GLuint vaoID;
            glGenVertexArrays(1, &vaoID);
            glBindVertexArray(vaoID);

            static const GLfloat vertices[] = {
               -1.0f, -1.0f, 0.0f, 1.0f,
               1.0f, -1.0f, 0.0f, 1.0f,
               0.0f,  1.0f, 0.0f, 1.0f,
            };

            GLuint vboID;
            glGenBuffers(1, &vboID);
            glBindBuffer(GL_ARRAY_BUFFER, vboID);
            
            glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

            // 1rst attribute buffer : vertices
            glEnableVertexAttribArray(0);
            glBindBuffer(GL_ARRAY_BUFFER, vboID);
            glVertexAttribPointer(
               0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
               4,                  // size
               GL_FLOAT,           // type
               GL_FALSE,           // normalized?
               0,                  // stride
               (void*)0            // array buffer offset
            );
             
            // Draw the triangle !
            glDrawArrays(GL_TRIANGLES, 0, 3); // Starting from vertex 0; 3 vertices total -> 1 triangle
             
            glDisableVertexAttribArray(0);
        }
    }
}

void mugg::graphics::Renderer::EndRender() {
}
