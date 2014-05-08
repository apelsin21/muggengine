#include "window.hpp"

void mugg::Window::ErrorCallback(int error, const char* message) {
    std::string error_msg(message);
    mugg::WriteToLog(mugg::ERROR, error_msg);
}

mugg::Window::Window() { 
    glfwSetErrorCallback(this->ErrorCallback);

    this->title = "MuggEngine Window";
    this->fullscreen = false;
    this->open = true;
    this->created = false;
    this->focused = false;
    this->minimized = false;

    if(!glfwInit()) {
        mugg::WriteToLog(mugg::FATAL_ERROR, "Failed to initialize GLFW!");
    }
}

mugg::Window::~Window() {
    glfwDestroyWindow(this->window);
}

void mugg::Window::Recreate() {
    if(!this->created)
        return;

    this->Create(this->title, this->resolution, this->position);
}

void mugg::Window::Create(std::string title = DefaultWindowTitle,
        glm::vec2 resolution = glm::vec2(DefaultWindowWidth, DefaultWindowHeight),
        glm::vec2 position = glm::vec2(0, 0)) {
    if(this->created) {
        mugg::WriteToLog(mugg::WARNING, "Tried to recreate window");
        return;
    }
    this->resolution = resolution;
    this->position = position;
    this->title = title;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);

    this->window = glfwCreateWindow(resolution.x, resolution.y, title.c_str(), NULL, NULL);

    if(!window) {
        std::string error_msg("Failed to create GLFW window wih resolution of: ");
        error_msg += resolution.x;
        error_msg += "x";
        error_msg += resolution.y;
        mugg::WriteToLog(mugg::FATAL_ERROR, error_msg);
        return;
    }

    glfwMakeContextCurrent(this->window);
}

bool mugg::Window::IsOpen() {
    return this->open;
}

void mugg::Window::SetWidth(int width) {
}
int mugg::Window::GetWidth() {
    return this->resolution.x;
}

void mugg::Window::SetHeight(int height) {
}
int mugg::Window::GetHeight() {
    return this->resolution.y;
}

void mugg::Window::SetResolution(glm::vec2 what) {
    this->resolution = what;
}
glm::vec2 mugg::Window::GetResolution() {
    int width, height;
    
    return glm::vec2(width, height);
}

void SetPosition(int x, int y) {

}

void mugg::Window::SwapBuffers() {
    glfwSwapBuffers(this->window);
}
