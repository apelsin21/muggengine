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
    this->modelLocation = 2;
    
    static const float vertex_positions[] = {
        -1.0f, -1.0f, 0.0f,
         1.0f,  1.0f, 0.0f,
        -1.0f,  1.0f, 0.0f,
        -1.0f, -1.0f, 0.0f,
         1.0f, -1.0f, 0.0f,
         1.0f,  1.0f, 0.0f, 
    };
    static const float vertex_uvs[] = {
        0.0f, 0.0f,
        1.0f, 1.0f,
        0.0f, 1.0f,
        0.0f, 0.0f,
        1.0f, 0.0f,
        1.0f, 1.0f,    
    };

    glBindVertexArray(this->vaoID);

    glGenBuffers(1, &this->positionBufferID);
    glGenBuffers(1, &this->uvBufferID);

    glBindBuffer(GL_ARRAY_BUFFER, this->positionBufferID);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertex_positions), vertex_positions, GL_STATIC_DRAW);

    glVertexAttribPointer(this->posLocation, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(this->posLocation);

    glBindBuffer(GL_ARRAY_BUFFER, this->uvBufferID);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertex_uvs), vertex_uvs, GL_STATIC_DRAW);

    glVertexAttribPointer(this->uvLocation, 2, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(this->uvLocation);
    
    glDisableVertexAttribArray(this->posLocation);
    glDisableVertexAttribArray(this->uvLocation);
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
            this->spriteBatches.push_back(new mugg::gui::SpriteBatch(this, 10000, this->vaoID, this->modelLocation));
        }
    } else {
        this->spriteBatches.push_back(new mugg::gui::SpriteBatch(this, 10000, this->vaoID, this->modelLocation));
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
    glUseProgram(this->programID);
    glBindVertexArray(this->vaoID);

    glEnableVertexAttribArray(this->posLocation);
    glEnableVertexAttribArray(this->uvLocation);
    for(unsigned int i = 0; i <= 4; i++) {
        glEnableVertexAttribArray(i + this->modelLocation); 
    }

    for(unsigned int i = 0; i < this->spriteBatches.size(); i++) {    

        for(unsigned int u = 0; u < this->spritesToBeUpdated.size(); u++) {
            this->spriteBatches[i]->UpdateSprite(this->sprites[this->spritesToBeUpdated[u]]);
            this->spritesToBeUpdated.erase(this->spritesToBeUpdated.begin() + u);
            u--;
        }

        this->spriteBatches[i]->Render();
    }
}
