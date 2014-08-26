#version 130

in vec3 v_position;
in vec2 v_uv;
in vec3 v_normal;

out vec2 f_uv;
out vec3 f_normal;

uniform mat4 v_model;
uniform mat4 v_projection;

void main(void) {
   gl_Position = v_model * vec4(v_position, 1.0);
   f_uv = v_uv;
   f_normal = v_normal;
}
