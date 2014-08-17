#include "mouse.hpp"

mugg::core::Mouse::Mouse() {
}
mugg::core::Mouse::~Mouse() {
}

glm::vec2 mugg::core::Mouse::GetPosition() {
    int x = 0, y = 0;

    SDL_GetMouseState(&x, &y);

    return glm::vec2(x, y);
}
int mugg::core::Mouse::GetX() {
    int x = 0;

    SDL_GetMouseState(&x, NULL);

    return x;
}
int mugg::core::Mouse::GetY() {
    int y = 0;

    SDL_GetMouseState(&y, NULL);

    return y;
}

bool mugg::core::Mouse::IsLeftButtonDown() {
    return SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_LEFT);
}
bool mugg::core::Mouse::IsMiddleButtonDown() {
    return SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_MIDDLE);
}
bool mugg::core::Mouse::IsRightButtonDown() {
    return SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_RIGHT);
}
