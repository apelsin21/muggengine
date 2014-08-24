#include "spritebatch.hpp"

mugg::graphics::SpriteBatch::SpriteBatch(unsigned int maxSprites = 50000) {
    this->maxSprites = maxSprites;
    
    this->modelMatrixBuffer = -1;
    this->texID = -1;

    this->spriteCount = 0;

    glGenBuffers(1, &this->modelMatrixBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, this->modelMatrixBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(glm::mat4) * this->maxSprites, NULL, GL_DYNAMIC_DRAW);
}
mugg::graphics::SpriteBatch::~SpriteBatch() {
    glDeleteBuffers(1, &this->modelMatrixBuffer);
}

void mugg::graphics::SpriteBatch::Add(const glm::mat4& modelMatrix) {
    if(this->spriteCount != this->maxSprites && glIsBuffer(this->modelMatrixBuffer)) {
        glBindBuffer(GL_ARRAY_BUFFER, this->modelMatrixBuffer);
        glBufferSubData(GL_ARRAY_BUFFER, sizeof(glm::mat4) * this->spriteCount, sizeof(glm::mat4), (GLvoid*)(&modelMatrix[0]));
        this->spriteCount++;
    } else {
        std::cout << "Tried to add sprite to full spritebatch!\n";
    }
}
void mugg::graphics::SpriteBatch::Replace(unsigned int index, const glm::mat4& modelMatrix) {
    if(index <= this->spriteCount) {
        glBufferSubData(GL_ARRAY_BUFFER, sizeof(glm::mat4) * index, sizeof(glm::mat4), (GLvoid*)(&modelMatrix[0]));
    }
}
void mugg::graphics::SpriteBatch::Delete(unsigned int index) {
    if(index <= this->spriteCount) {
        glBufferSubData(GL_ARRAY_BUFFER, sizeof(glm::mat4) * index, sizeof(glm::mat4), (GLvoid*)NULL);
    }
}

unsigned int mugg::graphics::SpriteBatch::GetSpriteCount() {
    return this->spriteCount;
}
unsigned int mugg::graphics::SpriteBatch::GetMaxSprites() {
    return this->maxSprites;
}
GLuint mugg::graphics::SpriteBatch::GetModelMatrixBuffer() {
    return this->modelMatrixBuffer;
}

GLuint mugg::graphics::SpriteBatch::GetTexture() {
    return this->texID;
}
