#include "guimanager.hpp"
#include "image.hpp"

mugg::gui::GUIManager::GUIManager(mugg::core::Engine* parent) {
    this->parent = parent;
    
    this->positionBuffer = -1;
    this->modelMatrixBuffer = -1;

    this->vaoID = -1;
    this->vsID = -1;
    this->fsID = -1;
    this->programID = -1;

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
    for(unsigned int i = 0; i < this->spriteBatches.size(); i++) {
        if(this->spriteBatches[i] != nullptr) {
            delete this->spriteBatches[i];
        }
    }
}

mugg::gui::Image* mugg::gui::GUIManager::CreateImage() {
    Image* img = new Image(this, this->images.size());
    
    if(this->spriteBatches.empty()) {
        this->spriteBatches.push_back(new mugg::graphics::SpriteBatch(500));
    }
    else if(this->spriteBatches[this->spriteBatches.size() - 1]->GetSpriteCount() == this->spriteBatches[this->spriteBatches.size() - 1]->GetMaxSprites()) {
        this->spriteBatches.push_back(new mugg::graphics::SpriteBatch(500));
    }
    
    this->spriteBatches[this->spriteBatches.size() - 1]->Add(img->GetModelMatrix());

    img->SetSpriteBatchIndex(this->spriteBatches.size() - 1);

    for(unsigned int i = 0; i < 4; i++) {
        glEnableVertexAttribArray(2 + i);
        glVertexAttribPointer(2 + i, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (GLvoid*)(sizeof(glm::vec4) * i));
        glVertexAttribDivisor(2 + i, 1);
        glDisableVertexAttribArray(2 + i);
    }

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
    for(unsigned int i = 0; i < this->spriteBatches.size(); i++) {
        glEnableVertexAttribArray(0);
        glEnableVertexAttribArray(1);
        glEnableVertexAttribArray(2);

        //Model matrix buffer pointers (4*4)
        glEnableVertexAttribArray(3);
        glEnableVertexAttribArray(4);
        glEnableVertexAttribArray(5);
        glEnableVertexAttribArray(6);
        
        glUseProgram(this->programID);
        
        glBindVertexArray(this->vaoID);
        glBindBuffer(GL_ARRAY_BUFFER, this->spriteBatches[i]->GetModelMatrixBuffer());
        
        for(unsigned int u = 0; u < this->images.size(); u++) {
            if(this->images[i]->GetSpriteBatchIndex() == i && this->images[i]->HasChanged()) {
                std::cout << "Updating sprite " << u << std::endl;
                this->spriteBatches[i]->Replace(u, this->images[u]->GetModelMatrix());
            }
        }

        glBindTexture(GL_TEXTURE_2D, this->images[0]->GetTexture()->GetID());
        glDrawArraysInstanced(GL_TRIANGLES, 0, this->spriteBatches[i]->GetSpriteCount() * 6, this->spriteBatches[i]->GetSpriteCount());
        
        glDisableVertexAttribArray(0);
        glDisableVertexAttribArray(1);
        
        glDisableVertexAttribArray(2);
        glDisableVertexAttribArray(3);
        glDisableVertexAttribArray(4);
        glDisableVertexAttribArray(5);
        glDisableVertexAttribArray(6);
    }
}
