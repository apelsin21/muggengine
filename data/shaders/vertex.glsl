#version 130

in vec4 in_position;
in vec2 in_uv;
in vec3 in_normal;

out vec2 out_uv;
out vec3 out_normal;

void main() {
    gl_Position = in_position; 
    
    out_uv = in_uv;
    out_normal = in_normal;
}
