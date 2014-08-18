#include "guimanager.hpp"
#include "image.hpp"

mugg::gui::GUIManager::GUIManager(mugg::core::Device* parent) {
    this->positionBuffer = -1;
    this->modelMatrixBuffer = -1;

    this->vaoID = -1;
    this->vsID = -1;
    this->fsID = -1;
    this->programID = -1;

    this->parent = parent;

    this->vsID = glCreateShader(GL_VERTEX_SHADER);
    this->fsID = glCreateShader(GL_FRAGMENT_SHADER);
    this->programID = glCreateProgram();

    mugg::graphics::Shader vertexShader;
    mugg::graphics::Shader fragmentShader;
    mugg::graphics::ShaderProgram shaderProgram;

    vertexShader.SetID(this->vsID);
    fragmentShader.SetID(this->fsID);
    shaderProgram.SetID(this->programID);

    vertexShader.SetData(this->vsData);
    fragmentShader.SetData(this->fsData);

    vertexShader.Compile();
    fragmentShader.Compile();

    shaderProgram.AddShader(this->vsID);
    shaderProgram.AddShader(this->fsID);
    shaderProgram.Link();

    glGenVertexArrays(1, &this->vaoID);
    glGenBuffers(1, &this->positionBuffer);
    glGenBuffers(1, &this->modelMatrixBuffer);

    glBindVertexArray(this->vaoID);

    glBindBuffer(GL_ARRAY_BUFFER, this->modelMatrixBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(glm::mat4) * 100000, NULL, GL_DYNAMIC_DRAW);

    for(unsigned int i = 0; i < 4; i++) {
        glEnableVertexAttribArray(2 + i);
        glVertexAttribPointer(2 + i, 4, GL_FLOAT, GL_FALSE, sizeof(glm::vec4), (GLvoid*)(sizeof(glm::vec4) * i));
        glVertexAttribDivisor(2 + i, 1);
        glDisableVertexAttribArray(2 + i);
    }
    
    static const GLfloat g_vertex_buffer_data[] = {
        -1.0f, -1.0f, 0.0f, 0.0f,
        1.0f, 1.0f, 1.0f, 1.0f,
        -1.0f, 1.0f, 0.0f, 1.0f,
    
        -1.0f, -1.0f, 0.0f, 0.0f,
        1.0f, -1.0f, 1.0f, 0.0f,
        1.0f, 1.0f, 1.0f, 1.0f,
    };
    
    glBindBuffer(GL_ARRAY_BUFFER, this->positionBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);

    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4*sizeof(GLfloat), 0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4*sizeof(GLfloat), (GLvoid*)(2*sizeof(GLfloat)));

    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
}
mugg::gui::GUIManager::~GUIManager() {
    glDeleteBuffers(1, &this->positionBuffer);
    glDeleteBuffers(1, &this->modelMatrixBuffer);
    glDeleteVertexArrays(1, &this->vaoID);

    if(glIsShader(this->vsID)) {
        glDeleteShader(this->vsID);
    }
    if(glIsShader(this->fsID)) {
        glDeleteShader(this->fsID);
    }
    if(glIsProgram(this->programID)) {
        glDeleteProgram(this->programID);
    }

    for(unsigned int i = 0; i < this->images.size(); i++) {
        if(this->images[i] != nullptr) {
            delete this->images[i];
        }
    }
}

mugg::gui::Image* mugg::gui::GUIManager::CreateImage() {
    Image* img = new Image(this, this->images.size());
    
    this->images.push_back(img);
    
    return img;
}
std::size_t mugg::gui::GUIManager::GetNumberOfImages() {
    return this->images.size();
}
bool mugg::gui::GUIManager::GetImageByIndex(int index, mugg::gui::Image*& out_image) {
    if(index < 0 || index >= this->images.size() || this->images.empty()) {
        std::cout << "Tried to get image from GUIManager by out of binds index!\n";
        return false;
    }

    out_image = this->images[index];
    return true;
}

void mugg::gui::GUIManager::Render() {
    if(!this->images.empty()) {
        glEnableVertexAttribArray(0);
        glEnableVertexAttribArray(1);
        glEnableVertexAttribArray(2);
        glEnableVertexAttribArray(3);
        glEnableVertexAttribArray(4);
        glEnableVertexAttribArray(5);
        glEnableVertexAttribArray(6);
        glBindVertexArray(this->vaoID);
        glBindBuffer(GL_ARRAY_BUFFER, this->modelMatrixBuffer);
        glUseProgram(this->programID);

        for(unsigned int i = 0; i < this->images.size(); i++) {
            glBufferSubData(GL_ARRAY_BUFFER, sizeof(glm::mat4) * i, sizeof(glm::mat4), (GLvoid*)(&this->images[i]->GetModelMatrix()[0]));
        }

        glBindTexture(GL_TEXTURE_2D, this->images[0]->GetTexture()->GetID());
        glDrawArraysInstanced(GL_TRIANGLES, 0, this->images.size() * 6, this->images.size());
        
        glDisableVertexAttribArray(0);
        glDisableVertexAttribArray(1);
        glDisableVertexAttribArray(2);
        glDisableVertexAttribArray(3);
        glDisableVertexAttribArray(4);
        glDisableVertexAttribArray(5);
        glDisableVertexAttribArray(6);
    }
}
