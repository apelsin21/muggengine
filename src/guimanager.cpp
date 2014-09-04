#include "guimanager.hpp"
#include "sprite.hpp"

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

    for(unsigned int i = 0; i < this->sprites.size(); i++) {
        if(this->sprites[i] != nullptr) {
            delete this->sprites[i];
        }
    }
    for(unsigned int i = 0; i < this->spriteBatches.size(); i++) {
        if(this->spriteBatches[i] != nullptr) {
            delete this->spriteBatches[i];
        }
    }

    glDeleteVertexArrays(1, &this->vaoID);
}

void mugg::gui::GUIManager::UpdateSpriteBatches() {
    if(!this->spriteBatches.empty()) {
        unsigned int index = this->spriteBatches.size() - 1;
        std::size_t currentSize = this->spriteBatches[index]->GetSpriteCount();
        std::size_t maxSize = this->spriteBatches[index]->GetMaxSprites();
        
        if(currentSize >= maxSize) {
            this->spriteBatches.push_back(new mugg::gui::SpriteBatch(this, 10000, this->vaoID, this->posLocation, this->uvLocation, this->colLocation));
        }
    } else {
        this->spriteBatches.push_back(new mugg::gui::SpriteBatch(this, 10000, this->vaoID, this->posLocation, this->uvLocation, this->colLocation));
    }
}

mugg::gui::Sprite* mugg::gui::GUIManager::CreateSprite() {
    Sprite* sprite = new Sprite(this);
   
    this->UpdateSpriteBatches();
    this->spriteBatches[this->spriteBatches.size() - 1]->AddSprite(sprite);
    this->sprites.push_back(sprite);

    return sprite;
}
void mugg::gui::GUIManager::UpdateSprite(unsigned int index) {
    if(index <= this->sprites.size()) {
        this->spritesToBeUpdated.push_back(index);
    }
}
std::size_t mugg::gui::GUIManager::GetNumberOfSprites() {
    return this->sprites.size();
}
bool mugg::gui::GUIManager::GetSpriteByIndex(int index, mugg::gui::Sprite*& out_image) {
    if(index < 0 || index >= this->sprites.size() || this->sprites.empty()) {
        std::cout << "Tried to get image from GUIManager by out of binds index!\n";
        return false;
    }

    out_image = this->sprites[index];
    return true;
}

glm::mat4 mugg::gui::GUIManager::GetModelMatrix() {
    return this->modelMatrix;
}
void mugg::gui::GUIManager::SetModelMatrix(const glm::mat4& modelMatrix) {
    this->modelMatrix = modelMatrix;
}

mugg::gui::SpriteBatch* mugg::gui::GUIManager::CreateSpriteBatch() {
    this->UpdateSpriteBatches();

    return this->spriteBatches[this->spriteBatches.size() - 1];
}

GLuint mugg::gui::GUIManager::GetShaderProgramID() {
    return this->programID;
}
void mugg::gui::GUIManager::SetShaderProgramID(GLuint id) {
    this->programID = id;
}

void mugg::gui::GUIManager::Render() {
    if(!this->spriteBatches.empty()) {
        glUniformMatrix4fv(this->modelMatrixUniformLocation, 1, GL_FALSE, glm::value_ptr(this->modelMatrix));
    }
}
