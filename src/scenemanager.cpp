#include "scenemanager.hpp"

mugg::scene::SceneManager::SceneManager(mugg::core::Device* parent) {
    this->parent = parent;
}
mugg::scene::SceneManager::~SceneManager() {
    for(unsigned int i = 0; i < this->sceneNodes.size(); i++) {
        if(this->sceneNodes[i] != nullptr) {
            delete this->sceneNodes[i];
        }
    }
}

mugg::scene::SceneNode* mugg::scene::SceneManager::CreateSceneNode() {
    mugg::scene::SceneNode* node = new mugg::scene::SceneNode(this);

    this->sceneNodes.push_back(node);

    return node;
}
