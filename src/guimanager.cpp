#include "guimanager.hpp"
#include "image.hpp"

mugg::gui::GUIManager::GUIManager(mugg::core::Device* creator) {
    this->vboID = -1;
    this->vaoID = -1;
    this->ibID = -1;
    this->modelMatrixBuffer = -1;
    this->vsID = -1;
    this->fsID = -1;
    this->programID = -1;

    this->posLocation = -1;
    this->uvLocation = -1;
    this->modelLocation = -1;

    
    this->creator = creator;

    this->vsID = glCreateShader(GL_VERTEX_SHADER);
    this->fsID = glCreateShader(GL_FRAGMENT_SHADER);
    this->programID = glCreateProgram();

    mugg::graphics::Shader vertexShader;
    mugg::graphics::Shader fragmentShader;
    mugg::graphics::ShaderProgram shaderProgram;

    vertexShader.SetID(this->vsID);
    fragmentShader.SetID(this->fsID);
    shaderProgram.SetID(this->programID);

    vertexShader.SetData(this->vsData);
    fragmentShader.SetData(this->fsData);

    vertexShader.Compile();
    fragmentShader.Compile();

    shaderProgram.AddShader(this->vsID);
    shaderProgram.AddShader(this->fsID);
    shaderProgram.Link();

    this->posLocation = glGetAttribLocation(this->programID, "v_pos");
    this->uvLocation = glGetAttribLocation(this->programID, "v_uv");
    
    glGenVertexArrays(1, &this->vaoID);
    glGenBuffers(1, &this->vboID);

    static const GLfloat g_vertex_buffer_data[] = {
        -1.0f, -1.0f, 0.0f, 0.0f,
        1.0f, 1.0f, 1.0f, 1.0f,
        -1.0f, 1.0f, 0.0f, 1.0f,

        -1.0f, -1.0f, 0.0f, 0.0f,
        1.0f, -1.0f, 1.0f, 0.0f,
        1.0f, 1.0f, 1.0f, 1.0f,
    };

    glBindVertexArray(this->vaoID);
    glBindBuffer(GL_ARRAY_BUFFER, this->vboID);
    glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);

    glEnableVertexAttribArray(this->posLocation);
    glEnableVertexAttribArray(this->uvLocation);
    
    glVertexAttribPointer(this->posLocation, 2, GL_FLOAT, GL_FALSE, 4*sizeof(GLfloat), 0);
    glVertexAttribPointer(this->uvLocation, 2, GL_FLOAT, GL_FALSE, 4*sizeof(GLfloat), (GLvoid*)(2*sizeof(GLfloat)));
    
    glDisableVertexAttribArray(this->posLocation);
    glDisableVertexAttribArray(this->uvLocation);
}
mugg::gui::GUIManager::~GUIManager() {
    glDeleteBuffers(1, &this->vboID);
    glDeleteVertexArrays(1, &this->vaoID);

    if(glIsShader(this->vsID)) {
        glDeleteShader(this->vsID);
    }
    if(glIsShader(this->fsID)) {
        glDeleteShader(this->fsID);
    }
    if(glIsProgram(this->programID)) {
        glDeleteProgram(this->programID);
    }

    for(unsigned int i = 0; i < this->images.size(); i++) {
        if(this->images[i] != nullptr) {
            delete this->images[i];
        }
    }
    for(unsigned int i = 0; i < this->textures.size(); i++) {
        if(glIsTexture(this->textures[i])) {
            glDeleteShader(this->textures[i]);
        }
    }
}

void mugg::gui::GUIManager::SetObjectPosition(unsigned int index, glm::vec2 position) {
    this->positions[index] = position;
}
glm::vec2 mugg::gui::GUIManager::GetObjectPosition(unsigned int index) {
    return this->positions[index];
}

void mugg::gui::GUIManager::SetObjectTexture(unsigned int index, GLuint texture) {
    this->textures[index] = texture;
}
GLuint mugg::gui::GUIManager::GetObjectTexture(unsigned int index) {
    return this->textures[index];
}

mugg::gui::Image* mugg::gui::GUIManager::CreateImage() {
    Image* img = new Image(this, this->images.size());
    
    this->images.push_back(img);

    //Needed so that their indices map correctly
    this->textures.push_back(0);
    this->positions.push_back(glm::vec2(0, 0));
    
    return img;
}
std::size_t mugg::gui::GUIManager::GetNumberOfImages() {
    return this->images.size();
}
bool mugg::gui::GUIManager::GetImageByIndex(int index, mugg::gui::Image*& out_image) {
    if(index < 0 || index >= this->images.size() || this->images.empty()) {
        std::cout << "Tried to get image from GUIManager by out of binds index!\n";
        return false;
    }

    out_image = this->images[index];
    return true;
}

void mugg::gui::GUIManager::Render() {
    glEnableVertexAttribArray(this->posLocation);
    glEnableVertexAttribArray(this->uvLocation);
    glEnableVertexAttribArray(this->modelLocation);

    glBindVertexArray(this->vaoID);
    glUseProgram(this->programID);
    
    glBindTexture(GL_TEXTURE_2D, this->textures[this->textures.size() - 1]);

    glDrawArraysInstanced(GL_TRIANGLES, 0, 6, this->images.size());
    
    glDisableVertexAttribArray(this->posLocation);
    glDisableVertexAttribArray(this->uvLocation);
    glDisableVertexAttribArray(this->modelLocation);
}
