#include "headers/shaderprogram.hpp"

ShaderProgram::ShaderProgram(const char* vsFilepath, const char* fsFilepath) {
    this->vsID = glCreateShader(GL_VERTEX_SHADER);
    this->fsID = glCreateShader(GL_FRAGMENT_SHADER);
    this->programID = glCreateProgram();

    this->vsSrc = this->loadShader(vsFilepath);
    this->fsSrc = this->loadShader(fsFilepath);

    this->compileShader(this->vsID, vsSrc);
    this->compileShader(this->fsID, fsSrc);

    this->link();
}

ShaderProgram::~ShaderProgram() {
}

std::string ShaderProgram::loadShader(const char* filepath) {
    std::string src;
    std::ifstream stream(filepath, std::ios::in);

    if(stream.is_open()) {
        std::string line = "";
        while(std::getline(stream, line)) {
            src += "\n" + line;
        }
        stream.close();
    }

    return src;
}

void ShaderProgram::compileShader(GLuint id, std::string shader) {
    const char* src = shader.c_str();
    glShaderSource(id, 1, &src, NULL);
    glCompileShader(id);

    GLint status;

    glGetShaderiv(id, GL_COMPILE_STATUS, &status);
    if(status != GL_TRUE) {
        GLint length;
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
        char message[length];

        glGetShaderInfoLog(id, length, NULL, message);
        std::cout << message << std::endl;
    }
}

void ShaderProgram::link() {
    this->programID = glCreateProgram();

    glAttachShader(this->programID, this->vsID);
	
    glAttachShader(this->programID, this->fsID);
    glLinkProgram(this->programID);

    GLint status;

    glGetProgramiv(this->programID, GL_LINK_STATUS, &status);
    if(status != GL_TRUE) {
        GLint length;
        glGetProgramiv(this->programID, GL_INFO_LOG_LENGTH, &length);
        char message[length];

        glGetProgramInfoLog(this->programID, length, NULL, message);
        std::cerr << message << std::endl;
    }

    glDeleteShader(this->vsID);
    glDeleteShader(this->fsID);
}

GLuint ShaderProgram::getProgramID() {
    return this->programID;
}

GLuint ShaderProgram::getVertexShaderID() {
    return this->vsID;
}

GLuint ShaderProgram::getFragmentShaderID() {
    return this->fsID;
}
