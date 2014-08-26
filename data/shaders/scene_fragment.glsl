#version 130

in vec2 f_uv;
in vec3 f_normal;

out vec4 out_color;

uniform sampler2D sampler;

void main(void) {
    out_color = texture(sampler, f_uv);
}
