#include "device.hpp"

mugg::core::Device::Device() {
}
mugg::core::Device::~Device() {
    for(unsigned int i = 0; i < this->guiManagers.size(); i++) {
        if(this->guiManagers[i] != nullptr) {
            delete this->guiManagers[i];
        }
    }
    for(unsigned int i = 0; i < this->renderers.size(); i++) {
        if(this->renderers[i] != nullptr) {
            delete this->renderers[i];
        }
    }
    for(unsigned int i = 0; i < this->contentManagers.size(); i++) {
        if(this->contentManagers[i] != nullptr) {
            delete this->contentManagers[i];
        }
    }
    for(unsigned int i = 0; i < this->windows.size(); i++) {
        if(this->windows[i] != nullptr) {
            delete this->windows[i];
        }
    }
    
}

mugg::gui::GUIManager* mugg::core::Device::CreateGUIManager() {
    gui::GUIManager* mgr = new gui::GUIManager(this);
    
    this->guiManagers.push_back(mgr);

    return mgr;
}
std::size_t mugg::core::Device::GetNumberOfGUIManagers() {
    return this->guiManagers.size();
}
bool mugg::core::Device::GetGUIManagerByIndex(int index, mugg::gui::GUIManager*& out_mgr) {
    if(index >= this->guiManagers.size() || index < 0 || this->guiManagers.empty()) {
        std::cout << "Tried to get GUIManager by out of bounds index.\n";
        return false;
    }

    out_mgr = this->guiManagers[index];
    return true;
}

mugg::core::ContentManager* mugg::core::Device::CreateContentManager() {
    core::ContentManager* mgr = new core::ContentManager(this);

    this->contentManagers.push_back(mgr);

    return mgr;
}
std::size_t mugg::core::Device::GetNumberOfContentManagers() {
    return this->contentManagers.size();
}
bool mugg::core::Device::GetContentManagerByIndex(int index, mugg::core::ContentManager*& out_mgr) {
    if(index >= this->contentManagers.size() || index < 0 || this->contentManagers.empty()) {
        std::cout << "Tried to get ContentManager by out of bounds index.\n";
        return false;
    }

    out_mgr = this->contentManagers[index];
    return true;
}

mugg::core::Window* mugg::core::Device::CreateWindow() {
    core::Window* window = new core::Window(this);

    this->windows.push_back(window);

    return window;
}
std::size_t mugg::core::Device::GetNumberOfWindows() {
    return this->windows.size();
}
bool mugg::core::Device::GetWindowByIndex(int index, mugg::core::Window*& out_window) {
    if(index >= this->windows.size() || index < 0 || this->windows.empty()) {
        std::cout << "Tried to get Window by out of bounds index.\n";
        return false;
    }

    out_window = this->windows[index];
    return true;
}

mugg::graphics::Renderer* mugg::core::Device::CreateRenderer() {
    graphics::Renderer* renderer = new graphics::Renderer(this);

    this->renderers.push_back(renderer);

    return renderer;
}
std::size_t mugg::core::Device::GetNumberOfRenderers() {
    return this->renderers.size();
}
bool mugg::core::Device::GetRendererByIndex(int index, mugg::graphics::Renderer*& out_renderer) {
    if(index >= this->renderers.size() || index < 0 || this->renderers.empty()) {
        std::cout << "Tried to get Renderer by out of bounds index.\n";
        return false;
    }

    out_renderer = this->renderers[index];
    return true;
}

mugg::scene::SceneManager* mugg::core::Device::CreateSceneManager() {
    scene::SceneManager* mgr = new scene::SceneManager(this);

    this->sceneManagers.push_back(mgr);

    return mgr;
}
std::size_t mugg::core::Device::GetNumberOfSceneManagers() {
    return this->sceneManagers.size();
}
bool mugg::core::Device::GetSceneManagerByIndex(int index, mugg::scene::SceneManager*& out_sceneManager) {
    if(index >= this->sceneManagers.size() || index < 0 || this->sceneManagers.empty()) {
        std::cout << "Tried to get Renderer by out of bounds index.\n";
        return false;
    }

    out_sceneManager = this->sceneManagers[index];
    return true;
}

mugg::net::NetManager* mugg::core::Device::CreateNetManager() {
    mugg::net::NetManager* mgr = new mugg::net::NetManager(this);

    this->netManagers.push_back(mgr);

    return mgr;
}
std::size_t mugg::core::Device::GetNumberOfNetManagers() {
    return this->netManagers.size();
}
bool mugg::core::Device::GetNetManagerByIndex(int index, mugg::net::NetManager*& out_netManager) {
    if(index >= this->netManagers.size() || index < 0 || this->netManagers.empty()) {
        std::cout << "Tried to get NetManager by out of bounds index.\n";
        return false;
    }

    out_netManager = this->netManagers[index];
    return true;
}

void mugg::core::Device::Render() {
    for(unsigned int i = 0; i < this->renderers.size(); i++) {
        this->renderers[i]->Draw();
    }
    for(unsigned int i = 0; i < this->guiManagers.size(); i++) {
        this->guiManagers[i]->Render();
    }
    for(unsigned int i = 0; i < this->sceneManagers.size(); i++) {
        this->sceneManagers[i]->Render();
    }
    for(unsigned int i = 0; i < this->windows.size(); i++) {
        this->windows[i]->SwapBuffers();
    }
}
