#include "spritebatch.hpp"

mugg::graphics::SpriteBatch::SpriteBatch(unsigned int maxSprites, GLuint vaoID, GLint posLocation, GLint uvLocation, GLint colLocation) {
    this->positionBufferID = -1;
    this->uvBufferID = -1;
    this->colorBufferID = -1;
    this->texID = -1;
    this->spriteCount = 0;
    this->positionCount = 0;
    this->uvCount = 0;
    this->colorCount = 0;
    this->maxSprites = maxSprites;
    this->posLocation = posLocation;
    this->uvLocation = uvLocation;
    this->colLocation = colLocation;

    glGenVertexArrays(1, &this->vaoID);
    glBindVertexArray(this->vaoID);

    
    //(3 POS, 2 UV, 3 COL) * 6
    static const GLfloat vertex_position_data[] = {
        -1.0f, -1.0f, 0.0f, 
         1.0f,  1.0f, 0.0f,
        -1.0f,  1.0f, 0.0f,
        -1.0f, -1.0f, 0.0f,
         1.0f, -1.0f, 0.0f,
         1.0f,  1.0f, 0.0f,
    };

    static const GLfloat vertex_uv_data[] = {
        0.0f, 0.0f,
        1.0f, 1.0f,
        0.0f, 1.0f,
        0.0f, 0.0f,
        1.0f, 0.0f,
        1.0f, 1.0f,
    };

    static const GLfloat vertex_color_data[] = {
        1.0f, 1.0f, 1.0f,
        1.0f, 1.0f, 1.0f,
        1.0f, 1.0f, 1.0f,
        1.0f, 1.0f, 1.0f,
        1.0f, 1.0f, 1.0f,
        1.0f, 1.0f, 1.0f,
    };

    //POSITION VERTEX DATA====================================================================================================================
    glEnableVertexAttribArray(this->posLocation);
    
    glGenBuffers(1, &this->positionBufferID);
    glBindBuffer(GL_ARRAY_BUFFER, this->positionBufferID);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertex_position_data), NULL, GL_STATIC_DRAW);

    for(unsigned int i = 0; i < this->maxSprites; i++) {
        glBufferSubData(GL_ARRAY_BUFFER, sizeof(vertex_position_data) * i, sizeof(vertex_position_data), (GLvoid*)(vertex_position_data));
    }

    glVertexAttribPointer(this->posLocation, 3, GL_FLOAT, GL_FALSE, 0, 0);

    glDisableVertexAttribArray(this->posLocation);
    //POSITION VERTEX DATA====================================================================================================================
    
    //UV VERTEX DATA====================================================================================================================
    glEnableVertexAttribArray(this->uvLocation);
    
    glGenBuffers(1, &this->uvBufferID);
    glBindBuffer(GL_ARRAY_BUFFER, this->uvBufferID);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertex_uv_data), NULL, GL_STATIC_DRAW);

    for(unsigned int i = 0; i < this->maxSprites; i++) {
        glBufferSubData(GL_ARRAY_BUFFER, sizeof(vertex_uv_data) * i, sizeof(vertex_uv_data), (GLvoid*)(vertex_uv_data));
    }

    glVertexAttribPointer(this->uvLocation, 2, GL_FLOAT, GL_FALSE, 0, 0);

    glDisableVertexAttribArray(this->uvLocation);
    //UV VERTEX DATA====================================================================================================================
    
    //COLOR VERTEX DATA====================================================================================================================
    glEnableVertexAttribArray(this->colLocation);
    
    glGenBuffers(1, &this->colorBufferID);
    glBindBuffer(GL_ARRAY_BUFFER, this->colorBufferID);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertex_color_data), NULL, GL_STATIC_DRAW);

    for(unsigned int i = 0; i < this->maxSprites; i++) {
        glBufferSubData(GL_ARRAY_BUFFER, sizeof(vertex_color_data) * i, sizeof(vertex_color_data), (GLvoid*)(vertex_color_data));
    }

    glVertexAttribPointer(this->colLocation, 3, GL_FLOAT, GL_FALSE, 0, 0);

    glDisableVertexAttribArray(this->colLocation);
    //COLOR VERTEX DATA====================================================================================================================
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

void mugg::graphics::SpriteBatch::Add() {
    if(this->spriteCount < this->maxSprites) {
        this->spriteCount++;
    } else {
        //Shouldn't ever happen, the parent GUIManager should always create a new one at the correct time,
        //but you never know
        std::cout << "Tried to add sprite to full spritebatch!\n";
    }
}
void mugg::graphics::SpriteBatch::UpdatePosition(unsigned int index, const glm::vec3& position) {
    if(index <= this->spriteCount * 6) {
        glBindBuffer(GL_ARRAY_BUFFER, this->positionBufferID);
        glBufferSubData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * index, sizeof(glm::vec3), (GLvoid*)(&position[0]));
    }
}
void mugg::graphics::SpriteBatch::UpdateUV(unsigned int index, const glm::vec2& uv) {
}
void mugg::graphics::SpriteBatch::UpdateColor(unsigned int index, const glm::vec3& color) {
}
void mugg::graphics::SpriteBatch::UpdateSprite(unsigned int index, const glm::mat4& modelMatrix) {
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
