#include "spritebatch.hpp"
#include "sprite.hpp"

mugg::gui::SpriteBatch::SpriteBatch(mugg::gui::GUIManager* parent, unsigned int maxSprites, GLuint vaoID, GLint posLocation, GLint uvLocation, GLint colLocation) {
    //Initialize default values
    this->vboID = -1;
    this->texID = -1;
    this->spriteCount = 0;
    this->positionsCount = 0;
    this->uvsCount = 0;
    this->colorsCount = 0;
    
    //Initialize member variables with parameters
    this->parent = parent;
    this->maxSprites = maxSprites;
    this->posLocation = posLocation;
    this->uvLocation = uvLocation;
    this->colLocation = colLocation;
    this->vaoID = vaoID;
   
    this->bufferSize = (18+12+18) * (this->maxSprites * sizeof(float));
    this->stride = (18+12+18) * sizeof(float);
        
    glBindVertexArray(this->vaoID);

    glEnableVertexAttribArray(this->posLocation);
    glEnableVertexAttribArray(this->uvLocation);
    glEnableVertexAttribArray(this->colLocation);
    
    glGenBuffers(1, &this->vboID);
    glBindBuffer(GL_ARRAY_BUFFER, this->vboID);
    glBufferData(GL_ARRAY_BUFFER, (sizeof(GLfloat) * (3*6)) * this->maxSprites, NULL, GL_STATIC_DRAW);

    glVertexAttribPointer(this->posLocation, 3, GL_FLOAT, GL_FALSE, this->stride, 0);
    glVertexAttribPointer(this->uvLocation, 2, GL_FLOAT, GL_FALSE, this->stride, (GLvoid*)(sizeof(float) * 18));
    glVertexAttribPointer(this->colLocation, 3, GL_FLOAT, GL_FALSE, this->stride, (GLvoid*)(sizeof(float) * (18+12)));

    glDisableVertexAttribArray(this->posLocation);
    glDisableVertexAttribArray(this->uvLocation);
    glDisableVertexAttribArray(this->colLocation);
}
mugg::gui::SpriteBatch::~SpriteBatch() {
    if(glIsBuffer(this->vboID) == GL_TRUE) {
        glDeleteBuffers(1, &this->vboID);
    }
}

//TODO: Figure out cleaner way to do this
void mugg::gui::SpriteBatch::AddSprite(mugg::gui::Sprite* sprite) {
    sprite->SetIndex(this->spriteCount);
    this->spriteCount++;

    this->UpdatePositions(sprite->GetPositions());
    this->positionsCount++;
    
    this->UpdateUVs(sprite->GetUVs());
    this->uvsCount++;
    
    this->UpdateColors(sprite->GetColors());
    this->colorsCount++;
}

int mugg::gui::SpriteBatch::GetCurrentBufferOffset() {
    return  (this->positionsCount * (sizeof(float) * 18)) +
            (this->uvsCount * (sizeof(float) * 12)) +
            (this->colorsCount * (sizeof(float) * 18));
}

void mugg::gui::SpriteBatch::UpdatePositions(const std::vector<float>& positions) {
    glBindVertexArray(this->vaoID);
    glBindBuffer(GL_ARRAY_BUFFER, this->vboID);
    glBufferSubData(GL_ARRAY_BUFFER, this->GetCurrentBufferOffset(), sizeof(float) * positions.size(), (GLvoid*)(&positions[0]));
}
void mugg::gui::SpriteBatch::UpdateUVs(const std::vector<float>& uvs) {
    glBindVertexArray(this->vaoID);
    glBindBuffer(GL_ARRAY_BUFFER, this->vboID);
    glBufferSubData(GL_ARRAY_BUFFER, this->GetCurrentBufferOffset(), sizeof(float) * uvs.size(), (GLvoid*)(&uvs[0]));
}
void mugg::gui::SpriteBatch::UpdateColors(const std::vector<float>& colors) {
    glBindVertexArray(this->vaoID);
    glBindBuffer(GL_ARRAY_BUFFER, this->vboID);
    glBufferSubData(GL_ARRAY_BUFFER, this->GetCurrentBufferOffset(), sizeof(float) * colors.size(), (GLvoid*)(&colors[0]));
}

unsigned int mugg::gui::SpriteBatch::GetSpriteCount() {
    return this->spriteCount;
}
unsigned int mugg::gui::SpriteBatch::GetMaxSprites() {
    return this->maxSprites;
}

GLuint mugg::gui::SpriteBatch::GetVBOID() {
    return this->vboID;
}
GLuint mugg::gui::SpriteBatch::GetTextureID() {
    return this->texID;
}
void mugg::gui::SpriteBatch::SetTextureID(GLuint id) {
    this->texID = id;
}

void mugg::gui::SpriteBatch::Render() {
    if(glIsProgram(this->parent->GetShaderProgramID()))
        glUseProgram(this->parent->GetShaderProgramID());
    else
        std::cout << "Spritebatch has invalid program id\n";
    
    glBindVertexArray(this->vaoID);
    
    glEnableVertexAttribArray(this->posLocation);
    glEnableVertexAttribArray(this->uvLocation);
    glEnableVertexAttribArray(this->colLocation);
    
    if(glIsTexture(this->texID))
        glBindTexture(GL_TEXTURE_2D, this->texID);
    else
        std::cout << this->texID << " isn't a texture!\n";

    glDrawArrays(GL_TRIANGLES, 0, this->spriteCount * 6);

    glDisableVertexAttribArray(this->posLocation);
    glDisableVertexAttribArray(this->uvLocation);
    glDisableVertexAttribArray(this->colLocation);
}
