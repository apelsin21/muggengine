#include "spritebatch.hpp"

mugg::graphics::SpriteBatch::SpriteBatch(unsigned int maxSprites, GLuint vaoID, GLint posLocation, GLint uvLocation, GLint colLocation) {
    this->vboID = -1;
    this->texID = -1;
    this->spriteCount = 0;
    this->positionCount = 0;
    this->uvCount = 0;
    this->colorCount = 0;

    this->maxSprites = maxSprites;
    this->vaoID = vaoID;

    this->posLocation = posLocation;
    this->uvLocation = uvLocation;
    this->colLocation = colLocation;

    glBindVertexArray(this->vaoID);

    this->stride = ((sizeof(glm::vec3) * 12) + (sizeof(glm::vec2)*6));

    glEnableVertexAttribArray(this->posLocation);
    glEnableVertexAttribArray(this->uvLocation);
    glEnableVertexAttribArray(this->colLocation);
    
    glGenBuffers(1, &this->vboID);
    glBindBuffer(GL_ARRAY_BUFFER, this->vboID);
    glBufferData(GL_ARRAY_BUFFER, ((sizeof(glm::vec3) * 12) + sizeof(glm::vec2) * 6) * this->maxSprites, NULL, GL_DYNAMIC_DRAW);
    
    glVertexAttribPointer(this->posLocation, 3, GL_FLOAT, GL_FALSE, this->stride, 0);
    glVertexAttribPointer(this->uvLocation, 2, GL_FLOAT, GL_FALSE, this->stride, (GLvoid*)(sizeof(glm::vec3)));
    glVertexAttribPointer(this->colLocation, 3, GL_FLOAT, GL_FALSE, this->stride, (GLvoid*)(sizeof(glm::vec3) + sizeof(glm::vec2)));

    glDisableVertexAttribArray(this->posLocation);
    glDisableVertexAttribArray(this->uvLocation);
    glDisableVertexAttribArray(this->colLocation);
    
}
mugg::graphics::SpriteBatch::~SpriteBatch() {
    if(glIsBuffer(this->vboID) == GL_TRUE) {
        glDeleteBuffers(1, &this->vboID);
    }
}

void mugg::graphics::SpriteBatch::Add() {
    if(this->spriteCount < this->maxSprites) {
        //Add default values so it is onscreen even when you haven't explicitly set the sprite's position.
        //Position default values
        //this->UpdateSprite(this->spriteCount, glm::mat4(1.0f));
       
        //Bottom left vertex
        this->UpdatePosition(this->spriteCount, glm::vec3(-1.0f, -1.0f, 0.0f));
        this->UpdateUV(this->spriteCount, glm::vec2(0.0f, 0.0f));
        this->UpdateColor(this->spriteCount, glm::vec3(1.0f, 1.0f, 1.0f));
        
        //Top right vertex
        this->UpdatePosition(this->spriteCount + 1, glm::vec3(1.0f, 1.0f, 0.0f));
        this->UpdateUV(this->spriteCount + 1, glm::vec2(1.0f, 1.0f));
        this->UpdateColor(this->spriteCount + 1, glm::vec3(1.0f, 1.0f, 1.0f));
        
        //Top left vertex
        this->UpdatePosition(this->spriteCount + 2, glm::vec3(-1.0f, 1.0f, 0.0f));
        this->UpdateUV(this->spriteCount + 2, glm::vec2(0.0f, 1.0f));
        this->UpdateColor(this->spriteCount + 2, glm::vec3(1.0f, 1.0f, 1.0f));
        
        //Bottom left vertex
        this->UpdatePosition(this->spriteCount + 3, glm::vec3(-1.0f, -1.0f, 0.0f));
        this->UpdateUV(this->spriteCount + 3, glm::vec2(0.0f, 0.0f));
        this->UpdateColor(this->spriteCount + 3, glm::vec3(1.0f, 1.0f, 1.0f));
        
        //Bottom right vertex
        this->UpdatePosition(this->spriteCount + 4, glm::vec3(1.0f, -1.0f, 0.0f));
        this->UpdateUV(this->spriteCount + 4, glm::vec2(1.0f, 0.0f));
        this->UpdateColor(this->spriteCount + 4, glm::vec3(1.0f, 1.0f, 1.0f));
        
        //Top right vertex
        this->UpdatePosition(this->spriteCount + 5, glm::vec3(1.0f, 1.0f, 0.0f));
        this->UpdateUV(this->spriteCount + 5, glm::vec2(1.0f, 1.0f));
        this->UpdateColor(this->spriteCount + 5, glm::vec3(1.0f, 1.0f, 1.0f));
        
        this->spriteCount++;
        this->positionCount += 6;
        this->uvCount += 6;
        this->colorCount += 6;
    } else {
        //Shouldn't ever happen, the parent GUIManager should always create a new one at the correct time,
        //but you never know
        std::cout << "Tried to add sprite to full spritebatch!\n";
    }
}
void mugg::graphics::SpriteBatch::UpdatePosition(unsigned int index, const glm::vec3& position) {
    if(index <= this->spriteCount * 6) {
        glBindVertexArray(vaoID);
        glBindBuffer(GL_ARRAY_BUFFER, this->vboID);
        glBufferSubData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * index, sizeof(glm::vec3), (GLvoid*)(&position[0]));
    
        glVertexAttribPointer(this->posLocation, 3, GL_FLOAT, GL_FALSE, this->stride, 0);
        glEnableVertexAttribArray(this->posLocation);
    }
}
void mugg::graphics::SpriteBatch::UpdateUV(unsigned int index, const glm::vec2& uv) {
    if(index <= this->spriteCount * 6) {
        glBindVertexArray(vaoID);
        glBindBuffer(GL_ARRAY_BUFFER, this->vboID);
        glBufferSubData(GL_ARRAY_BUFFER, sizeof(glm::vec2) * index, sizeof(glm::vec2), (GLvoid*)(&uv[0]));
    
        glVertexAttribPointer(this->uvLocation, 2, GL_FLOAT, GL_FALSE, this->stride, (GLvoid*)(sizeof(glm::vec3)));
        glEnableVertexAttribArray(this->uvLocation);
    }
}
void mugg::graphics::SpriteBatch::UpdateColor(unsigned int index, const glm::vec3& color) {
    if(index <= this->spriteCount * 6) {
        glBindVertexArray(this->vaoID);
        glBindBuffer(GL_ARRAY_BUFFER, this->vboID);
        glBufferSubData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * index, sizeof(glm::vec3), (GLvoid*)(&color[0]));
    
        glVertexAttribPointer(this->colLocation, 3, GL_FLOAT, GL_FALSE, this->stride, (GLvoid*)(sizeof(glm::vec3) + sizeof(glm::vec2)));
        glEnableVertexAttribArray(this->colLocation);
    }
}
void mugg::graphics::SpriteBatch::UpdateSprite(unsigned int index, const glm::mat4& modelMatrix) {
    if(index <= this->spriteCount) {
        glm::vec4 bottomLeft  = glm::vec4(-1.0f, -1.0f, 0.0f, 1.0f) * modelMatrix; 
        glm::vec4 topRight    = glm::vec4( 1.0f,  1.0f, 0.0f, 1.0f) * modelMatrix; 
        glm::vec4 topLeft     = glm::vec4(-1.0f,  1.0f, 0.0f, 1.0f) * modelMatrix; 
        glm::vec4 bottomRight = glm::vec4( 1.0f, -1.0f, 0.0f, 1.0f) * modelMatrix; 

        this->UpdatePosition(this->spriteCount + 0, glm::vec3(bottomLeft));
        this->UpdatePosition(this->spriteCount + 1, glm::vec3(topRight));
        this->UpdatePosition(this->spriteCount + 2, glm::vec3(topLeft));
        this->UpdatePosition(this->spriteCount + 3, glm::vec3(bottomLeft));
        this->UpdatePosition(this->spriteCount + 4, glm::vec3(bottomRight));
        this->UpdatePosition(this->spriteCount + 5, glm::vec3(topLeft));
    }
}

unsigned int mugg::graphics::SpriteBatch::GetSpriteCount() {
    return this->spriteCount;
}
unsigned int mugg::graphics::SpriteBatch::GetMaxSprites() {
    return this->maxSprites;
}

GLuint mugg::graphics::SpriteBatch::GetVBOID() {
    return this->vboID;
}

GLuint mugg::graphics::SpriteBatch::GetTextureID() {
    return this->texID;
}

void mugg::graphics::SpriteBatch::Render() {
    glBindVertexArray(this->vaoID);
    
    glEnableVertexAttribArray(this->posLocation);
    glEnableVertexAttribArray(this->uvLocation);
    glEnableVertexAttribArray(this->colLocation);

    glBindTexture(GL_TEXTURE_2D, 1);
    glDrawArrays(GL_TRIANGLES, 0, this->spriteCount * 6);
    
    glDisableVertexAttribArray(this->posLocation);
    glDisableVertexAttribArray(this->uvLocation);
    glDisableVertexAttribArray(this->colLocation);
}
