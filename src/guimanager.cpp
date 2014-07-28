#include "guimanager.hpp"
#include "image.hpp"

mugg::gui::GUIManager::GUIManager(mugg::core::Device* creator) {
    this->creator = creator;

    this->vsID = glCreateShader(GL_VERTEX_SHADER);
    this->fsID = glCreateShader(GL_FRAGMENT_SHADER);
    this->programID = glCreateProgram();

    mugg::graphics::Shader* vertexShader = new mugg::graphics::Shader();
    mugg::graphics::Shader* fragmentShader = new mugg::graphics::Shader();
    mugg::graphics::ShaderProgram* shaderProgram = new mugg::graphics::ShaderProgram();

    vertexShader->SetID(this->vsID);
    fragmentShader->SetID(this->fsID);
    shaderProgram->SetID(this->programID);

    vertexShader->SetData(this->vsData);
    fragmentShader->SetData(this->fsData);

    vertexShader->Compile();
    fragmentShader->Compile();

    shaderProgram->AddShader(this->vsID);
    shaderProgram->AddShader(this->fsID);
    shaderProgram->Link();

    delete vertexShader;
    delete fragmentShader;
    delete shaderProgram;

    this->posLocation = glGetAttribLocation(this->programID, "v_pos");
    this->uvLocation = glGetAttribLocation(this->programID, "v_uv");

    glGenVertexArrays(1, &this->vaoID);
    glGenBuffers(1, &this->vboID);

    static const GLfloat g_vertex_buffer_data[] = {
        -1.0f, -1.0f,
        1.0f, 1.0f,
        -1.0f, 1.0f,

        -1.0f, -1.0f,
        1.0f, 1.0f,
        1.0f, -1.0f
    };

    glBindVertexArray(this->vaoID);
    glBindBuffer(GL_ARRAY_BUFFER, this->vboID);
    glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);

    glEnableVertexAttribArray(this->posLocation);
    glEnableVertexAttribArray(this->uvLocation);
    
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);
    
    glDisableVertexAttribArray(this->posLocation);
    glDisableVertexAttribArray(this->uvLocation);
}
mugg::gui::GUIManager::~GUIManager() {
    glDeleteBuffers(1, &this->vboID);
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
        delete this->images[i];
    }
    for(unsigned int i = 0; i < this->textures.size(); i++) {
        if(glIsTexture(this->textures[i])) {
            glDeleteShader(this->textures[i]);
        }
    }
}

void mugg::gui::GUIManager::SetObjectPosition(unsigned int index, glm::vec2 position) {
    this->positions[index] = position;
}
glm::vec2 mugg::gui::GUIManager::GetObjectPosition(unsigned int index) {
    return this->positions[index];
}

void mugg::gui::GUIManager::SetObjectTexture(unsigned int index, GLuint texture) {
    this->textures[index] = texture;
}
GLuint mugg::gui::GUIManager::GetObjectTexture(unsigned int index) {
    return this->textures[index];
}

mugg::gui::Image* mugg::gui::GUIManager::GetImage() {
    Image* img = new Image(this, this->images.size());
    
    this->images.push_back(img);

    //Needed so that their indices map correctly
    this->textures.push_back(0);
    this->positions.push_back(glm::vec2(0, 0));
    
    return img;
}

void mugg::gui::GUIManager::Render() {
    glEnableVertexAttribArray(this->posLocation);
    glEnableVertexAttribArray(this->uvLocation);
    
    glUseProgram(this->programID);
    
    for(unsigned int i = 0; i < this->images.size(); i++)
        glBindTexture(GL_TEXTURE_2D, this->images[i]->GetTexture());

    glBindVertexArray(this->vaoID);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    
    glDisableVertexAttribArray(this->posLocation);
    glDisableVertexAttribArray(this->uvLocation);
}
