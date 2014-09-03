#include "spritebatch.hpp"

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
    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * (3*6), NULL, GL_DYNAMIC_DRAW);

    glVertexAttribPointer(this->posLocation, 3, GL_FLOAT, GL_FALSE, 0, 0);

    glBindBuffer(GL_ARRAY_BUFFER, this->uvBufferID);
    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * (2*6), NULL, GL_DYNAMIC_DRAW);

    glVertexAttribPointer(this->uvLocation, 2, GL_FLOAT, GL_FALSE, 0, 0);

    glBindBuffer(GL_ARRAY_BUFFER, this->colorBufferID);
    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * (3*6), NULL, GL_DYNAMIC_DRAW);
    
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
void mugg::graphics::SpriteBatch::Add() {
    if(this->spriteCount < this->maxSprites) {
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

        //POSITION
        glBindBuffer(GL_ARRAY_BUFFER, this->positionBufferID);
        glBufferSubData(GL_ARRAY_BUFFER, sizeof(vertex_position_data) * this->spriteCount, sizeof(vertex_position_data), (GLvoid*)(vertex_position_data));
        
        //UV
        glBindBuffer(GL_ARRAY_BUFFER, this->uvBufferID);
        glBufferSubData(GL_ARRAY_BUFFER, sizeof(vertex_uv_data) * this->spriteCount, sizeof(vertex_uv_data), (GLvoid*)(vertex_uv_data));
        
        //COLOR
        glBindBuffer(GL_ARRAY_BUFFER, this->colorBufferID);
        glBufferSubData(GL_ARRAY_BUFFER, sizeof(vertex_color_data) * this->spriteCount, sizeof(vertex_color_data), (GLvoid*)(vertex_color_data));
        
        this->spriteCount++;
    } else {
        //Shouldn't ever happen, the parent GUIManager should always create a new one at the correct time,
        //but you never know
        std::cout << "Tried to add sprite to full spritebatch!\n";
    }
}
void mugg::graphics::SpriteBatch::UpdatePosition(unsigned int index, const glm::vec3& position) {
    if(index <= this->spriteCount * 6) {
        glBindVertexArray(this->vaoID);
        glBindBuffer(GL_ARRAY_BUFFER, this->positionBufferID);
        glBufferSubData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * index, sizeof(glm::vec3), (GLvoid*)(&position[0]));
    } else {
        std::cout << "Tried to update vertex position for out of bounds sprite\n";
    }
}
void mugg::graphics::SpriteBatch::UpdateUV(unsigned int index, const glm::vec2& uv) {
    if(index <= this->spriteCount * 6) {
        glBindVertexArray(this->vaoID);
        glBindBuffer(GL_ARRAY_BUFFER, this->uvBufferID);
        glBufferSubData(GL_ARRAY_BUFFER, sizeof(glm::vec2) * index, sizeof(glm::vec2), (GLvoid*)(&uv[0]));
    } else {
        std::cout << "Tried to update vertex UVs for out of bounds sprite\n";
    }
}
void mugg::graphics::SpriteBatch::UpdateColor(unsigned int index, const glm::vec3& color) {
    if(index <= this->spriteCount * 6) {
        glBindVertexArray(this->vaoID);
        glBindBuffer(GL_ARRAY_BUFFER, this->colorBufferID);
        glBufferSubData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * index, sizeof(glm::vec3), (GLvoid*)(&color[0]));
    } else {
        std::cout << "Tried to update vertex colors for out of bounds sprite\n";
    }
}
void mugg::graphics::SpriteBatch::UpdateSprite(unsigned int index, const glm::mat4& modelMatrix) {
    if(index <= this->spriteCount) {
        glm::vec3 bottomLeft  = glm::vec3(glm::vec4(-1.0f, -1.0f, 0.0f, 1.0f) * modelMatrix); 
        glm::vec3 topRight    = glm::vec3(glm::vec4( 1.0f,  1.0f, 0.0f, 1.0f) * modelMatrix);
        glm::vec3 topLeft     = glm::vec3(glm::vec4(-1.0f,  1.0f, 0.0f, 1.0f) * modelMatrix);
        glm::vec3 bottomRight = glm::vec3(glm::vec4( 1.0f, -1.0f, 0.0f, 1.0f) * modelMatrix);

        this->UpdatePosition(index + 0, bottomLeft);
        this->UpdatePosition(index + 1, topRight);
        this->UpdatePosition(index + 2, topLeft);
        this->UpdatePosition(index + 3, bottomLeft);
        this->UpdatePosition(index + 4, bottomRight);
        this->UpdatePosition(index + 5, topRight);
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
