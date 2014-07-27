#include "device.hpp"

mugg::core::Device::Device() {
    glfwInit();
}
mugg::core::Device::~Device() {
    this->guiManagers.clear();
    this->renderers.clear();
    this->contentManagers.clear();
    this->windows.clear();

    glfwTerminate();
}

mugg::gui::GUIManager* mugg::core::Device::GetGUIManager() {
    gui::GUIManager* mgr = new gui::GUIManager(this);
    
    this->guiManagers.push_back(mgr);

    return mgr;
}

mugg::core::ContentManager* mugg::core::Device::GetContentManager() {
    core::ContentManager* mgr = new core::ContentManager(this);

    this->contentManagers.push_back(mgr);

    return mgr;
}

mugg::core::Window* mugg::core::Device::GetWindow() {
    core::Window* window = new core::Window(this);

    this->windows.push_back(window);

    return window;
}

mugg::graphics::Renderer* mugg::core::Device::GetRenderer() {
    graphics::Renderer* renderer = new graphics::Renderer(this);

    this->renderers.push_back(renderer);

    return renderer;
}
