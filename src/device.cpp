#include "device.hpp"

mugg::core::Device::Device() {
}
mugg::core::Device::~Device() {
    for(unsigned int i = 0; i < this->guiManagers.size(); i++) {
        delete this->guiManagers[i];
    }
    for(unsigned int i = 0; i < this->renderers.size(); i++) {
        delete this->renderers[i];
    }
    for(unsigned int i = 0; i < this->contentManagers.size(); i++) {
        delete this->contentManagers[i];
    }
    for(unsigned int i = 0; i < this->windows.size(); i++) {
        delete this->windows[i];
    }
    
}

mugg::gui::GUIManager* mugg::core::Device::CreateGUIManager() {
    gui::GUIManager* mgr = new gui::GUIManager(this);
    
    this->guiManagers.push_back(mgr);

    return mgr;
}

mugg::core::ContentManager* mugg::core::Device::CreateContentManager() {
    core::ContentManager* mgr = new core::ContentManager(this);

    this->contentManagers.push_back(mgr);

    return mgr;
}

mugg::core::Window* mugg::core::Device::CreateWindow() {
    core::Window* window = new core::Window(this);

    this->windows.push_back(window);

    return window;
}

mugg::graphics::Renderer* mugg::core::Device::CreateRenderer() {
    graphics::Renderer* renderer = new graphics::Renderer(this);

    this->renderers.push_back(renderer);

    return renderer;
}
