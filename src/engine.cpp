#include "engine.hpp"

mugg::core::Engine::Engine() {
    this->window = new mugg::core::Window(this);
    this->renderer = new mugg::graphics::Renderer(this);
    this->contentManager = new mugg::core::ContentManager(this);
    this->sceneManager = new mugg::scene::SceneManager(this);
    this->netManager = new mugg::net::NetManager(this);
    this->guiManager = new mugg::gui::GUIManager(this);
}
mugg::core::Engine::~Engine() {
    if(this->guiManager != nullptr) {
        delete this->guiManager;
    }
    if(this->renderer != nullptr) {
        delete this->renderer;
    }
    if(this->sceneManager != nullptr) {
        delete this->sceneManager;
    }
    if(this->netManager != nullptr) {
        delete this->netManager;
    }
    if(this->contentManager != nullptr) {
        delete this->contentManager;
    }
    if(this->window != nullptr) {
        delete this->window;
    }
}

mugg::gui::GUIManager* mugg::core::Engine::GetGUIManager() {
    return this->guiManager;
}

mugg::core::ContentManager* mugg::core::Engine::GetContentManager() {
    return this->contentManager;
}

mugg::core::Window* mugg::core::Engine::GetWindow() {
    return this->window;
}

mugg::graphics::Renderer* mugg::core::Engine::GetRenderer() {
    return this->renderer;
}

mugg::scene::SceneManager* mugg::core::Engine::GetSceneManager() {
    return this->sceneManager;
}

mugg::net::NetManager* mugg::core::Engine::GetNetManager() {
    return this->netManager;
}

void mugg::core::Engine::Render() {
    this->renderer->Render();
    this->guiManager->Render();
    this->sceneManager->Render();
    this->window->SwapBuffers();
}
