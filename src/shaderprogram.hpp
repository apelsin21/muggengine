#ifndef SHADERPROGRAM_HPP
#define SHADERPROGRAM_HPP

#include <GL/glew.h>

#include <string>
#include <vector>
#include <fstream>
#include <iostream>

#include <cstdlib>
#include <cstdio>

class ShaderProgram {
private:
    GLuint programID;
    GLuint vsID, fsID;
    std::string vsSrc, fsSrc;

    std::string loadShader(const char* filepath);
    void compileShader(GLuint id, std::string shader);
    void link();
public:
    ShaderProgram(const char* vsFilepath, const char* fsFilepath);
    ~ShaderProgram();

    GLuint getProgramID();
    GLuint getVertexShaderID();
    GLuint getFragmentShaderID();

    void addShader(const char* filepath);
};

#endif // SHADERPROGRAM_HPP
