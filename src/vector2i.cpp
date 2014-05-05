#include "vector2i.hpp"

mugg::Vector2i::Vector2i(int x, int y) {
    this->vec.x = x;
    this->vec.y = y;
}

void mugg::Vector2i::SetX(int x) {
    this->vec.x = x;
}
int mugg::Vector2i::GetX() {
    return this->vec.x;
}

void mugg::Vector2i::SetY(int y) {
    this->vec.y = y;
}
int mugg::Vector2i::GetY() {
    return this->vec.y;
}
