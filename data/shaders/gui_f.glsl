#version 330 core

in vec2 f_uv;
in vec3 f_color;

out vec4 color;

uniform sampler2D sampler;

void main() {
    color = vec4(f_color.rgb, 1.0) * texture(sampler, f_uv);
}
