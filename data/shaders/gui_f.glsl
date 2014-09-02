#version 330 core

in vec2 f_uv;
in vec3 f_color;

out vec4 color;

uniform sampler2D sampler;

void main() {
    color =  texture(sampler, f_uv) * vec4(color.rgb, 1.0);
}
