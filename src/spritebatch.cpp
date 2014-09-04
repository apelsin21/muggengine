#include "spritebatch.hpp"
#include "sprite.hpp"

mugg::graphics::SpriteBatch::SpriteBatch(unsigned int maxSprites, GLuint vaoID, GLint posLocation, GLint uvLocation, GLint colLocation) {
    //Initialize default values
    this->positionBufferID = -1;
    this->uvBufferID = -1;
    this->colorBufferID = -1;
    this->texID = -1;
    this->spriteCount = 0;
    this->positionCount = 0;
    this->uvCount = 0;
    this->colorCount = 0;
    
    //Initialize member variables with parameters
    this->maxSprites = maxSprites;
    this->posLocation = posLocation;
    this->uvLocation = uvLocation;
    this->colLocation = colLocation;
    this->vaoID = vaoID;
    
    glBindVertexArray(this->vaoID);

    glEnableVertexAttribArray(this->posLocation);
    glEnableVertexAttribArray(this->uvLocation);
    glEnableVertexAttribArray(this->colLocation);
    
    glGenBuffers(1, &this->positionBufferID);
    glGenBuffers(1, &this->uvBufferID);
    glGenBuffers(1, &this->colorBufferID);
    
    glBindBuffer(GL_ARRAY_BUFFER, this->positionBufferID);
    glBufferData(GL_ARRAY_BUFFER, (sizeof(GLfloat) * (3*6)) * this->maxSprites, NULL, GL_DYNAMIC_DRAW);

    glVertexAttribPointer(this->posLocation, 3, GL_FLOAT, GL_FALSE, 0, 0);

    glBindBuffer(GL_ARRAY_BUFFER, this->uvBufferID);
    glBufferData(GL_ARRAY_BUFFER, (sizeof(GLfloat) * (2*6)) * this->maxSprites, NULL, GL_DYNAMIC_DRAW);

    glVertexAttribPointer(this->uvLocation, 2, GL_FLOAT, GL_FALSE, 0, 0);

    glBindBuffer(GL_ARRAY_BUFFER, this->colorBufferID);
    glBufferData(GL_ARRAY_BUFFER, (sizeof(GLfloat) * (3*6)) * this->maxSprites, NULL, GL_DYNAMIC_DRAW);
    
    glVertexAttribPointer(this->colLocation, 3, GL_FLOAT, GL_FALSE, 0, 0);

    glDisableVertexAttribArray(this->posLocation);
    glDisableVertexAttribArray(this->uvLocation);
    glDisableVertexAttribArray(this->colLocation);
}
mugg::graphics::SpriteBatch::~SpriteBatch() {
    if(glIsBuffer(this->positionBufferID) == GL_TRUE) {
        glDeleteBuffers(1, &this->positionBufferID);
    }
    if(glIsBuffer(this->uvBufferID) == GL_TRUE) {
        glDeleteBuffers(1, &this->uvBufferID);
    }
    if(glIsBuffer(this->colorBufferID) == GL_TRUE) {
        glDeleteBuffers(1, &this->colorBufferID);
    }
}

//TODO: Figure out cleaner way to do this
void mugg::graphics::SpriteBatch::AddSprite(mugg::gui::Sprite* sprite) {
    sprite->SetIndex(this->spriteCount);
    this->spriteCount++;
    this->UpdateSprite(sprite);
}
void mugg::graphics::SpriteBatch::UpdateSprite(mugg::gui::Sprite* sprite) {
    unsigned int index = sprite->GetIndex();
    
    if(index <= this->spriteCount) {
        if(sprite->IsPositionChanged()) {
            this->UpdatePositions(index, sprite->GetPositions());
        }
        if(sprite->IsUVChanged()) {
            this->UpdateUVs(index, sprite->GetUVs());
        }
        if(sprite->IsColorChanged()) {
            this->UpdateColors(index, sprite->GetColors());
        }
    }
}

void mugg::graphics::SpriteBatch::UpdatePositions(unsigned int index, const std::vector<float>& positions) {
    if(index <= this->spriteCount) {
        glBindVertexArray(this->vaoID);
        glBindBuffer(GL_ARRAY_BUFFER, this->positionBufferID);
        glBufferSubData(GL_ARRAY_BUFFER, (sizeof(float) * positions.size()) * index, sizeof(float) * positions.size(), (GLvoid*)(&positions[0]));
    } else {
        std::cout << "Tried to update vertex position for out of bounds sprite\n";
    }
}
void mugg::graphics::SpriteBatch::UpdateUVs(unsigned int index, const std::vector<float>& uvs) {
    if(index <= this->spriteCount) {
        glBindVertexArray(this->vaoID);
        glBindBuffer(GL_ARRAY_BUFFER, this->uvBufferID);
        glBufferSubData(GL_ARRAY_BUFFER, (sizeof(float) * uvs.size()) * index, sizeof(float) * uvs.size(), (GLvoid*)(&uvs[0]));
    } else {
        std::cout << "Tried to update vertex UVs for out of bounds sprite\n";
    }
}
void mugg::graphics::SpriteBatch::UpdateColors(unsigned int index, const std::vector<float>& colors) {
    if(index <= this->spriteCount) {
        glBindVertexArray(this->vaoID);
        glBindBuffer(GL_ARRAY_BUFFER, this->colorBufferID);
        glBufferSubData(GL_ARRAY_BUFFER, (sizeof(float) * colors.size()) * index, sizeof(float) * colors.size(), (GLvoid*)(&colors[0]));
    } else {
        std::cout << "Tried to update vertex colors for out of bounds sprite\n";
    }
}

unsigned int mugg::graphics::SpriteBatch::GetSpriteCount() {
    return this->spriteCount;
}
unsigned int mugg::graphics::SpriteBatch::GetMaxSprites() {
    return this->maxSprites;
}

GLuint mugg::graphics::SpriteBatch::GetPositionBufferID() {
    return this->positionBufferID;
}
GLuint mugg::graphics::SpriteBatch::GetUVBufferID() {
    return this->uvBufferID;
}
GLuint mugg::graphics::SpriteBatch::GetColorBufferID() {
    return this->colorBufferID;
}

GLuint mugg::graphics::SpriteBatch::GetTextureID() {
    return this->texID;
}

void mugg::graphics::SpriteBatch::Render() {
    glBindVertexArray(this->vaoID);
    
    glEnableVertexAttribArray(this->posLocation);
    glEnableVertexAttribArray(this->uvLocation);
    glEnableVertexAttribArray(this->colLocation);
    
    if(glIsTexture(1))
        glBindTexture(GL_TEXTURE_2D, 1);
    else
        std::cout << "1 isn't a texture!\n";
    
    glDrawArrays(GL_TRIANGLES, 0, this->spriteCount * 6);

    glDisableVertexAttribArray(this->posLocation);
    glDisableVertexAttribArray(this->uvLocation);
    glDisableVertexAttribArray(this->colLocation);
}
