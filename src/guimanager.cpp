#include "guimanager.hpp"
#include "image.hpp"

mugg::gui::GUIManager::GUIManager(mugg::core::Engine* parent) {
    this->parent = parent;

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

    this->posLocation   = 0; 
    this->uvLocation    = 1; 
    this->colLocation   = 2; 
    this->modelLocation = 3; 
}

mugg::gui::GUIManager::~GUIManager() {
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

    glDeleteVertexArrays(1, &this->vaoID);
}

mugg::gui::Image* mugg::gui::GUIManager::CreateImage() {
    Image* img = new Image(this, this->images.size());
    
    if(this->spriteBatches.empty()) {
        this->spriteBatches.push_back(new mugg::graphics::SpriteBatch(10000, this->vaoID, this->posLocation, this->uvLocation, this->colLocation, this->modelLocation));
    }
    else if(this->spriteBatches[this->spriteBatches.size() - 1]->GetSpriteCount() == this->spriteBatches[this->spriteBatches.size() - 1]->GetMaxSprites()) {
        this->spriteBatches.push_back(new mugg::graphics::SpriteBatch(10000, this->vaoID, this->posLocation, this->uvLocation, this->colLocation, this->modelLocation));
    }
    
    this->spriteBatches[this->spriteBatches.size() - 1]->Add();
    
    img->SetSpriteBatchIndex(this->spriteBatches.size() - 1);
    
    this->images.push_back(img);

    return img;
}
void mugg::gui::GUIManager::UpdateImage(unsigned int index) {
    if(index <= this->images.size()) {
        this->imagesToBeUpdated.push_back(index);
    }
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
    glUseProgram(this->programID);
    glBindVertexArray(this->vaoID);

    for(unsigned int i = 0; i < this->spriteBatches.size(); i++) {
        for(unsigned int u = 0; u < this->imagesToBeUpdated.size(); u++) {
            std::cout << "Updating sprite " << u + 1 << " of " << this->imagesToBeUpdated.size() << std::endl;
            this->spriteBatches[i]->UpdateModelMatrix(u, this->images[this->imagesToBeUpdated[u]]->GetModelMatrix());
            this->imagesToBeUpdated.erase(this->imagesToBeUpdated.begin() + u);
            u--;
        }

        glVertexAttribPointer(this->posLocation, 2, GL_FLOAT, GL_FALSE, sizeof(glm::vec2), 0);
        glEnableVertexAttribArray(this->posLocation);
        glVertexAttribPointer(this->uvLocation, 2, GL_FLOAT, GL_FALSE, sizeof(glm::vec2), 0);
        glEnableVertexAttribArray(this->uvLocation);
        glVertexAttribPointer(this->colLocation, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), 0);
        glEnableVertexAttribArray(this->colLocation);
        for(unsigned int i = this->modelLocation; i < this->modelLocation + 5; i++) {
            glVertexAttribPointer(i, 4, GL_FLOAT, GL_FALSE, sizeof(glm::vec4), 0);
            glEnableVertexAttribArray(i);
        }

        this->spriteBatches[i]->Render();
    }
}
