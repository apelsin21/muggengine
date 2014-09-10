#include "guimanager.hpp"
#include "sprite.hpp"
#include "engine.hpp"

mugg::gui::GUIManager::GUIManager(mugg::core::Engine* parent) {
    this->parent = parent;

    this->vaoID = -1;

    this->posAttribName = "v_position";
    this->uvAttribName = "v_uv";
    this->modelAttribName = "v_model";
    this->projectionMatrixUniformName = "u_projection";

    this->vertexShader = new mugg::graphics::Shader(graphics::ShaderType::VertexShader, true);
    this->fragmentShader = new mugg::graphics::Shader(graphics::ShaderType::FragmentShader, true);
    this->shaderProgram = new mugg::graphics::ShaderProgram(true);

    this->vertexShader->Load("data/shaders/gui_v.glsl");
    this->fragmentShader->Load("data/shaders/gui_f.glsl");
    
    vertexShader->Compile();
    fragmentShader->Compile();

    shaderProgram->AttachShader(this->vertexShader);
    shaderProgram->AttachShader(this->fragmentShader);
    shaderProgram->Link();

    if(!this->shaderProgram->AddAttribute(this->posAttribName)) {
       std::cout << "GUIManager failed to get attribute " << this->posAttribName << "\n";
    }
    if(!this->shaderProgram->AddAttribute(this->uvAttribName)) {
       std::cout << "GUIManager failed to get attribute " << this->uvAttribName << "\n";
    }
    if(!this->shaderProgram->AddAttribute(this->modelAttribName)) {
        std::cout << "GUIManager failed to get attribute " << this->modelAttribName << "\n";
    }
    if(!this->shaderProgram->AddUniform(this->projectionMatrixUniformName)) {
       std::cout << "GUIManager failed to get uniform " << this->projectionMatrixUniformName << "\n";
    }

    glGenVertexArrays(1, &this->vaoID);
    
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

    glVertexAttribPointer(this->shaderProgram->GetAttribute(this->posAttribName), 3, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(this->shaderProgram->GetAttribute(this->posAttribName));

    glBindBuffer(GL_ARRAY_BUFFER, this->uvBufferID);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertex_uvs), vertex_uvs, GL_STATIC_DRAW);

    glVertexAttribPointer(this->shaderProgram->GetAttribute(this->uvAttribName), 2, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(this->shaderProgram->GetAttribute(this->uvAttribName));
    
    glDisableVertexAttribArray(this->shaderProgram->GetAttribute(this->posAttribName));
    glDisableVertexAttribArray(this->shaderProgram->GetAttribute(this->uvAttribName));
}

mugg::gui::GUIManager::~GUIManager() {
    this->shaderProgram->DeleteID();
    this->vertexShader->DeleteID();
    this->fragmentShader->DeleteID();

    delete this->shaderProgram;
    delete this->vertexShader;
    delete this->fragmentShader;

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
            this->spriteBatches.push_back(new mugg::gui::SpriteBatch(this, 10000, this->vaoID, this->shaderProgram->GetAttribute(this->modelAttribName)));
        }
    } else {
        this->spriteBatches.push_back(new mugg::gui::SpriteBatch(this, 10000, this->vaoID, this->shaderProgram->GetAttribute(this->modelAttribName)));
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

mugg::graphics::ShaderProgram* mugg::gui::GUIManager::GetShaderProgram() {
    return this->shaderProgram;
}
void mugg::gui::GUIManager::SetShaderProgram(mugg::graphics::ShaderProgram* program) {
    this->shaderProgram = program;
}

glm::mat4 mugg::gui::GUIManager::GetProjectionMatrix() {
    return this->projectionMatrix;
}
void mugg::gui::GUIManager::SetProjectionMatrix(const glm::mat4& mat) {
    this->projectionMatrix = mat;
}

void mugg::gui::GUIManager::Render() {
    this->shaderProgram->Use();
    glBindVertexArray(this->vaoID);

    glEnableVertexAttribArray(this->shaderProgram->GetAttribute(this->posAttribName));
    glEnableVertexAttribArray(this->shaderProgram->GetAttribute(this->uvAttribName));
    for(unsigned int i = 0; i <= 4; i++) {
        glEnableVertexAttribArray(i + this->shaderProgram->GetUniform(this->projectionMatrixUniformName)); 
    }

    glUniformMatrix4fv(this->shaderProgram->GetUniform(this->projectionMatrixUniformName), 1, GL_FALSE, glm::value_ptr(this->projectionMatrix));

    for(unsigned int i = 0; i < this->spriteBatches.size(); i++) {    
        for(unsigned int u = 0; u < this->spritesToBeUpdated.size(); u++) {
            this->spriteBatches[i]->UpdateSprite(this->sprites[this->spritesToBeUpdated[u]]);
            this->spritesToBeUpdated.erase(this->spritesToBeUpdated.begin() + u);
            u--;
        }

        this->spriteBatches[i]->Render();
    }
}
