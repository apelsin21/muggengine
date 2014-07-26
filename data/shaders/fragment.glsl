#version 130

in vec2 out_uv;
in vec3 out_normal;

out vec4 color;

uniform sampler2D sampler;

void main() {
    color = texture(sampler, out_uv);
}
