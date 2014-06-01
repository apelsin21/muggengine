#include "window.hpp"

mugg::Window::Window(glm::vec2 resolution, glm::vec2 position, const char* title = "MuggEngine Window") {
    this->window.create(sf::VideoMode((int)resolution.x, (int)resolution.y), title, sf::Style::Default, sf::ContextSettings(32));
    this->resolution = resolution;
    this->position = position;

    this->SetPosition(position);
    this->framerateLimit = 0;
    this->vsync = false;
    this->fullscreen = false;
    this->open = true;
    this->title = title;
}
mugg::Window::~Window() {
    this->window.close();
    
}

void mugg::Window::SetPosition(glm::vec2 position) {
    this->position = position;
    this->window.setPosition(sf::Vector2i((int)position.x, (int)position.y));
}
glm::vec2 mugg::Window::GetPosition() {
    return this->position;
}

void mugg::Window::SetResolution(glm::vec2 resolution) {
    this->resolution = resolution;
}
glm::vec2 mugg::Window::GetResolution() {
    return this->resolution;
}

void mugg::Window::SetFullscreen(bool fullscreen) {
    this->fullscreen = fullscreen;
}
bool mugg::Window::GetFullscreen() {
    return this->fullscreen;
}

void mugg::Window::SetVsync(bool enabled) {
    this->vsync = enabled;
    this->window.setVerticalSyncEnabled(enabled);
}
bool mugg::Window::GetVsync() {
    return this->vsync;
}

void mugg::Window::SetOpen(bool open) {
    if(!open) {
        this->open = false;
        this->window.close();
    } else {
        this->open = true;
    }
}
bool mugg::Window::IsOpen() {
    return this->open;
}
void mugg::Window::Close() {
    this->open = false;
    this->window.close();
}

void mugg::Window::SetActive(bool active) {
    this->active = active;
    this->window.setActive(active);
}
bool mugg::Window::GetActive() {
    return this->active;
}

void mugg::Window::SetTitle(const char* title) {
    this->title = title;
    this->window.setTitle(title);
}
const char* mugg::Window::GetTitle() {
    return this->title;
}

bool mugg::Window::Recreate() {
    return false;
}

void mugg::Window::SwapBuffers() {
    this->window.display();
}
