#version 330 core

layout(location = 0) in vec3 v_position;
layout(location = 1) in vec2 v_uv;
layout(location = 2) in vec3 v_normal;

out vec2 f_uv;
out vec3 f_normal;

uniform mat4 v_model;
uniform mat4 v_projection;

void main(void) {
   gl_Position = v_model * vec4(v_position, 1.0);
   f_uv = v_uv;
   f_normal = v_normal;
}
