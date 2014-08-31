#version 330 core

layout(location = 0) in vec3 v_position;
layout(location = 1) in vec2 v_uv;
layout(location = 2) in vec3 v_color;

out vec2 f_uv;
out vec3 f_color;

uniform mat4 u_model;

void main() {
    f_uv = v_uv;
    f_color = v_color;
    
    gl_Position = u_model * vec4(v_position, 1.0); 
}
