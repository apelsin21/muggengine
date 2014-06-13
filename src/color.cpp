#include "color.hpp"

mugg::graphics::Color::Color(float r, float g, float b, float a) {
    this->r = r;
    this->g = g;
    this->b = b;
    this->a = a;
    this->Clamp();
}

mugg::graphics::Color::Color() {
    this->r = 0.0f;
    this->g = 0.0f;
    this->b = 0.0f;
    this->a = 0.0f;
}

void mugg::graphics::Color::Clamp() {
    if(r < 0.0f)
        r = 0.0f;
    else if(r > 1.0f)
        r = 1.0f;

    if(g < 0.0f)
        g = 0.0f;
    else if(g > 1.0f)
        g = 1.0f;

    if(b < 0.0f)
        b = 0.0f;
    else if(b > 1.0f)
        b = 1.0f;

    if(a < 0.0f)
        a = 0.0f;
    else if(a > 1.0f)
        a = 1.0f;
}

void mugg::graphics::Color::Set(Color color) {
    this->r = color.r;
    this->g = color.g;
    this->b = color.b;
    this->a = color.a;
    this->Clamp();
}
void mugg::graphics::Color::Set(float r, float g, float b, float a) {
    this->r = r;
    this->g = g;
    this->b = b;
    this->a = a;
    this->Clamp();
}
