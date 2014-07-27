#include "guimanager.hpp"

mugg::gui::GUIManager::GUIManager() {
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

    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);
    
    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
}
mugg::gui::GUIManager::~GUIManager() {
    glDeleteBuffers(1, &this->vboID);
    glDeleteVertexArrays(1, &this->vaoID);
}

void mugg::gui::GUIManager::AddTexture2D(GLuint id) {
    this->textures.push_back(id);
}
GLuint mugg::gui::GUIManager::GetTexture2D(unsigned int index) {
    if(this->textures.empty() || index >= this->textures.size()) {
        std::cout << "Tried to get texture from GUIManager with out of bounds arg\n";
        return 0;
    }

    return this->textures[index];
}
void mugg::gui::GUIManager::RemoveTexture2D(unsigned int index) {
    if(this->textures.empty() || index >= this->textures.size()) {
        std::cout << "Tried to delete texture from GUIManager with out of bounds arg\n";
    } else {
        this->textures.erase(this->textures.begin() + index);
    }
}

void mugg::gui::GUIManager::Render() {
    for(unsigned int i = 0; i < this->textures.size(); i++) {
        if(glIsTexture(this->textures[i])) {
            glEnableVertexAttribArray(0);
            glEnableVertexAttribArray(1);
            
            glBindTexture(GL_TEXTURE_2D, this->textures[i]);
            glBindVertexArray(this->vaoID);
            glDrawArrays(GL_TRIANGLES, 0, 6);
            
            glDisableVertexAttribArray(0);
            glDisableVertexAttribArray(1);
        }
    }
}
