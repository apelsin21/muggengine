#include "window.hpp"

mugg::Window::Window() {
}

mugg::Window::~Window() {
    glfwDestroyWindow(this->window);
}

void mugg::Window::SetWidth(int width) {
}
int mugg::Window::GetWidth() {
    return this->resolution.GetX();
}

void mugg::Window::SetHeight(int height) {
}
int mugg::Window::GetHeight() {
    return this->resolution.GetY();
}

void mugg::Window::SetResolution(mugg::Vector2i what) {
    this->resolution = what;
}
mugg::Vector2i mugg::Window::GetResolution() {
    return this->resolution;
}

void SetPosition(int x, int y) {

}
