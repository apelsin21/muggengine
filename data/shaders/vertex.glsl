#version 130

layout(location = 0) in vec4 vertexPosition_modelspace;

void main(void) {
    gl_Position = vertexPosition_modelspace;
}
