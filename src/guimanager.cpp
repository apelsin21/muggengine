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

    std::string vsData, fsData;

    if(!mugg::io::LoadTextFromFile("data/shaders/gui_v.glsl", vsData)) {
        std::cout << "Failed to load vsData\n";
    }
    if(!mugg::io::LoadTextFromFile("data/shaders/gui_f.glsl", fsData)) {
        std::cout << "Failed to load fsData\n";
    }
    
    vertexShader.SetData(vsData);
    fragmentShader.SetData(fsData);

    vertexShader.Compile();
    fragmentShader.Compile();

    shaderProgram.AddShader(this->vsID);
    shaderProgram.AddShader(this->fsID);
    shaderProgram.Link();

    glGenVertexArrays(1, &this->vaoID);

    this->posLocation = 0; 
    this->uvLocation  = 1;
    this->colLocation = 2;
    
    this->modelMatrixUniformLocation = glGetUniformLocation(this->programID, "u_model");
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
    
    if(!this->spriteBatches.empty()) {
        unsigned int index = this->spriteBatches.size() - 1;
        std::size_t currentSize = this->spriteBatches[index]->GetSpriteCount();
        std::size_t maxSize = this->spriteBatches[index]->GetMaxSprites();
        
        if(currentSize >= maxSize) {
            this->spriteBatches.push_back(new mugg::graphics::SpriteBatch(10000, this->vaoID, this->posLocation, this->uvLocation, this->colLocation));
        }
    } else {
        this->spriteBatches.push_back(new mugg::graphics::SpriteBatch(10000, this->vaoID, this->posLocation, this->uvLocation, this->colLocation));
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

glm::mat4 mugg::gui::GUIManager::GetModelMatrix() {
    return this->modelMatrix;
}
void mugg::gui::GUIManager::SetModelMatrix(const glm::mat4& modelMatrix) {
    this->modelMatrix = modelMatrix;
}

void mugg::gui::GUIManager::Render() {
    if(glIsProgram(this->programID) == GL_TRUE && !this->spriteBatches.empty()) {
        glUseProgram(this->programID);
       
        glUniformMatrix4fv(this->modelMatrixUniformLocation, 1, GL_FALSE, glm::value_ptr(this->modelMatrix));

        //Render spritebatches
        for(unsigned int i = 0; i < this->spriteBatches.size(); i++) {
            //Update VBO in spritebatches where it is needed
            for(unsigned int u = 0; u < this->imagesToBeUpdated.size(); u++) {
                this->spriteBatches[i]->UpdateSprite(u, this->images[this->imagesToBeUpdated[u]]->GetModelMatrix());
                this->imagesToBeUpdated.erase(this->imagesToBeUpdated.begin() + u);
                u--;
            }

            if(this->spriteBatches[i]->GetSpriteCount() > 0) {
                this->spriteBatches[i]->Render();
            }
        }

    }
}
