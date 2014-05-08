#include "window.hpp"

void mugg::Window::ErrorCallback(int error, const char* message) {
    std::string error_msg(message);
    mugg::WriteToLog(mugg::ERROR, error_msg);
}

mugg::Window::Window() { 
    glfwSetErrorCallback(this->ErrorCallback);
    glfwSetWindowSizeCallback
    glfwSetWindowCloseCallback
    glfwSetWindowFocusCallback
    glfwSetWindowIconifyCallback
    glfwSetWindowPosCallback
    glfwSetWindowRefreshCallback

    if(!glfwInit()) {
        mugg::WriteToLog(mugg::FATAL_ERROR, "Failed to initialize GLFW!");
    }
}

mugg::Window::~Window() {
    glfwDestroyWindow(this->window);
}

void mugg::Window::Create(std::string title, glm::vec2 resolution, glm::vec2 position) {
    if(this->created) {
        mugg::WriteToLog(mugg::WARNING, "Tried to recreate window");
        return;
    }

    this->window = glfwCreateWindow(resolution.x, resolution.y, title.c_str(), NULL, NULL);
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
    return this->resolution;
}

void SetPosition(int x, int y) {

}
