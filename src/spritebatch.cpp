#include "spritebatch.hpp"

mugg::graphics::SpriteBatch::SpriteBatch(unsigned int maxSprites, GLuint vaoID, GLint posLocation, GLint uvLocation, GLint colLocation, GLint modelLocation) {
    this->positionBuffer = -1;
    this->uvBuffer = -1;
    this->colorBuffer = -1;
    this->modelMatrixBuffer = -1;
    this->texID = -1;
    this->spriteCount = 0;

    this->maxSprites = maxSprites;
    this->vaoID = vaoID;

    this->posLocation = posLocation;
    this->uvLocation = uvLocation;
    this->colLocation = colLocation;
    this->modelLocation = modelLocation;

    glBindVertexArray(this->vaoID);

    glEnableVertexAttribArray(this->posLocation);
    glEnableVertexAttribArray(this->uvLocation);
    glEnableVertexAttribArray(this->colLocation);
    for(unsigned int i = this->modelLocation; i < this->modelLocation + 4; i++) {
        glEnableVertexAttribArray(i);
    }
    
    //POSITION BUFFER
    glGenBuffers(1, &this->positionBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, this->positionBuffer);
    glBufferData(GL_ARRAY_BUFFER, (sizeof(glm::vec2) * 6) * this->maxSprites, NULL, GL_DYNAMIC_DRAW);
    
    glVertexAttribPointer(this->posLocation, 2, GL_FLOAT, GL_FALSE, 0, 0);

    //UV BUFFER
    glGenBuffers(1, &this->uvBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, this->uvBuffer);
    glBufferData(GL_ARRAY_BUFFER, (sizeof(glm::vec2) * 6) * this->maxSprites, NULL, GL_DYNAMIC_DRAW);
    
    glVertexAttribPointer(this->uvLocation, 2, GL_FLOAT, GL_FALSE, 0, 0);
    
    //COLOR BUFFER
    glGenBuffers(1, &this->colorBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, this->colorBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * this->maxSprites, NULL, GL_DYNAMIC_DRAW);
    
    glVertexAttribPointer(this->colLocation, 3, GL_FLOAT, GL_FALSE, 0, 0);

    //MODEL MATRIX BUFFER
    glGenBuffers(1, &this->modelMatrixBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, this->modelMatrixBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(glm::mat4) * this->maxSprites, NULL, GL_DYNAMIC_DRAW);
    
    for(unsigned int i = this->modelLocation; i < this->modelLocation + 4; i++) {
        glVertexAttribPointer(i, 4, GL_FLOAT, GL_FALSE, 0, 0);
    }

    glDisableVertexAttribArray(this->posLocation);
    glDisableVertexAttribArray(this->uvLocation);
    glDisableVertexAttribArray(this->colLocation);
    
    for(unsigned int i = 0; i < 4; i++) {
        glDisableVertexAttribArray(this->modelLocation + i);
    }
}
mugg::graphics::SpriteBatch::~SpriteBatch() {
    if(glIsBuffer(this->positionBuffer) == GL_TRUE) {
        glDeleteBuffers(1, &this->positionBuffer);
    }
    if(glIsBuffer(this->uvBuffer) == GL_TRUE) {
        glDeleteBuffers(1, &this->uvBuffer);
    }
    if(glIsBuffer(this->colorBuffer) == GL_TRUE) {
        glDeleteBuffers(1, &this->colorBuffer);
    }
    if(glIsBuffer(this->modelMatrixBuffer) == GL_TRUE) {
        glDeleteBuffers(1, &this->modelMatrixBuffer);
    }
}

void mugg::graphics::SpriteBatch::Add() {
    if(this->spriteCount < this->maxSprites) {
        //Position default values
        this->UpdatePosition(this->spriteCount, glm::vec2(-1.0f, -1.0f));
        this->UpdatePosition(this->spriteCount + 1, glm::vec2(1.0f, 1.0f));
        this->UpdatePosition(this->spriteCount + 2, glm::vec2(-1.0f, 1.0f));
        this->UpdatePosition(this->spriteCount + 3, glm::vec2(-1.0f, -1.0f));
        this->UpdatePosition(this->spriteCount + 4, glm::vec2(1.0f, -1.0f));
        this->UpdatePosition(this->spriteCount + 5, glm::vec2(1.0f, 1.0f));
        
        //UV default values
        this->UpdateUV(this->spriteCount, glm::vec2(0.0f, 0.0f));
        this->UpdateUV(this->spriteCount + 1, glm::vec2(1.0f, 1.0f));
        this->UpdateUV(this->spriteCount + 2, glm::vec2(0.0f, 1.0f));
        this->UpdateUV(this->spriteCount + 3, glm::vec2(0.0f, 0.0f));
        this->UpdateUV(this->spriteCount + 4, glm::vec2(1.0f, 0.0f));
        this->UpdateUV(this->spriteCount + 5, glm::vec2(1.0f, 1.0f));
       
        //Color default values
        this->UpdateColor(this->spriteCount, glm::vec3(1.0f, 1.0f, 1.0f));

        //Identity model matrix
        this->UpdateModelMatrix(this->spriteCount, glm::mat4(1.0f));
        
        this->spriteCount++;
    } else {
        std::cout << "Tried to add sprite to full spritebatch!\n";
    }
}
void mugg::graphics::SpriteBatch::UpdatePosition(unsigned int index, const glm::vec2& position) {
    if(index <= this->spriteCount) {
        glBindVertexArray(vaoID);
        glBindBuffer(GL_ARRAY_BUFFER, this->positionBuffer);
        glBufferSubData(GL_ARRAY_BUFFER, sizeof(glm::vec2) * index, sizeof(glm::vec2), (GLvoid*)(&position[0]));
    }
}
void mugg::graphics::SpriteBatch::UpdateUV(unsigned int index, const glm::vec2& uv) {
    if(index <= this->spriteCount) {
        glBindVertexArray(vaoID);
        glBindBuffer(GL_ARRAY_BUFFER, this->uvBuffer);
        glBufferSubData(GL_ARRAY_BUFFER, sizeof(glm::vec2) * index, sizeof(glm::vec2), (GLvoid*)(&uv[0]));
    }
}
void mugg::graphics::SpriteBatch::UpdateColor(unsigned int index, const glm::vec3& color) {
    if(index <= this->spriteCount) {
        glBindVertexArray(this->vaoID);
        glBindBuffer(GL_ARRAY_BUFFER, this->colorBuffer);
        glBufferSubData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * index, sizeof(glm::vec3), (GLvoid*)(&color[0]));
    }
}
void mugg::graphics::SpriteBatch::UpdateModelMatrix(unsigned int index, const glm::mat4& modelMatrix) {
    if(index <= this->spriteCount) {
        glBindVertexArray(this->vaoID);
        glBindBuffer(GL_ARRAY_BUFFER, this->modelMatrixBuffer);
        glBufferSubData(GL_ARRAY_BUFFER, sizeof(glm::mat4) * index, sizeof(glm::mat4), (GLvoid*)(&modelMatrix[0]));
    }
}

unsigned int mugg::graphics::SpriteBatch::GetSpriteCount() {
    return this->spriteCount;
}
unsigned int mugg::graphics::SpriteBatch::GetMaxSprites() {
    return this->maxSprites;
}

GLuint mugg::graphics::SpriteBatch::GetPositionBuffer() {
    return this->positionBuffer;
}
GLuint mugg::graphics::SpriteBatch::GetUVBuffer() {
    return this->uvBuffer;
}
GLuint mugg::graphics::SpriteBatch::GetColorBuffer() {
    return this->colorBuffer;
}
GLuint mugg::graphics::SpriteBatch::GetModelMatrixBuffer() {
    return this->modelMatrixBuffer;
}

GLuint mugg::graphics::SpriteBatch::GetTexture() {
    return this->texID;
}

void mugg::graphics::SpriteBatch::Render() {
    glBindBuffer(GL_ARRAY_BUFFER, this->positionBuffer);     
    glBindBuffer(GL_ARRAY_BUFFER, this->uvBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, this->colorBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, this->modelMatrixBuffer);

    glBindTexture(GL_TEXTURE_2D, 1);
    glDrawArrays(GL_TRIANGLES, 0, this->spriteCount * 6);
}
