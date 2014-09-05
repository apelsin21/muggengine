#version 330 core

layout(location = 0) in vec3 v_position;
layout(location = 1) in vec2 v_uv;
layout(location = 2) in mat4 v_model;

out vec2 f_uv;

void main() {
    f_uv = v_uv;
    gl_Position = v_model * vec4(v_position, 1.0); 
}
