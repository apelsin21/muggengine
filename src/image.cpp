#include "image.hpp"

mugg::gui::Image::Image() {
    this->hasValidTexture = false;
    this->begin = -1;
    this->end = -1;
}
mugg::gui::Image::Image(double x, double y) {
    this->SetXY(x, y);
    this->hasValidTexture = false;
    this->begin = -1;
    this->end = -1;
}
mugg::gui::Image::Image(mugg::graphics::Texture2D texture) {
    this->texture = texture;
    this->hasValidTexture = false;
    this->begin = -1;
    this->end = -1;
}
mugg::gui::Image::Image(double x, double y, mugg::graphics::Texture2D texture) {
    this->SetXY(x, y);
    this->texture = texture;
    this->hasValidTexture = false;
    this->begin = -1;
    this->end = -1;
}
mugg::gui::Image::~Image() {
}

void mugg::gui::Image::SetY(double y) {
    this->position.y = y;
}
void mugg::gui::Image::SetX(double x) {
    this->position.x = x;
}
void mugg::gui::Image::SetXY(double x, double y) {
    this->position.x = x;
    this->position.y = y;
}

double mugg::gui::Image::GetY() {
    return this->position.y;
}
double mugg::gui::Image::GetX() {
    return this->position.x;
}

void mugg::gui::Image::SetWidth(int width) {
    this->resolution.x = width;
}
void mugg::gui::Image::SetHeight(int height) {
    this->resolution.y = height;
}
void mugg::gui::Image::SetResolution(int width, int height) {
    this->resolution.x = width;
    this->resolution.y = height;
}

int mugg::gui::Image::GetWidth() {
    return this->resolution.x;
}
int mugg::gui::Image::GetHeight() {
    return this->resolution.y;
}

int mugg::gui::Image::GetBegin() {
    return this->begin;
}
int mugg::gui::Image::GetEnd() {
    return this->end;
}

void mugg::gui::Image::SetBegin(int begin) {
    this->begin = begin;
}
void mugg::gui::Image::SetEnd(int end) {
    this->end = end;
}

void mugg::gui::Image::SetTexture(mugg::graphics::Texture2D texture) {
    this->texture = texture;

    this->SetWidth(texture.GetWidth());
    this->SetHeight(texture.GetHeight());
}
mugg::graphics::Texture2D mugg::gui::Image::GetTexture() {
    return this->texture;
}

void mugg::gui::Image::SetColor(mugg::graphics::Color color) {
    this->color = color;
}
mugg::graphics::Color mugg::gui::Image::GetColor() {
    return this->color;
}
