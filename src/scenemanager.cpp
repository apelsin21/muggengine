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
std::size_t mugg::scene::SceneManager::GetNumberOfSceneNodes() {
    return this->sceneNodes.size();
}
bool mugg::scene::SceneManager::GetSceneNodeByIndex(int index, mugg::scene::SceneNode*& out_node) {
    if(index < 0 || index >= this->sceneNodes.size() || this->sceneNodes.empty()) {
        std::cout << "Tried to get scenenode from scenemanager, with out of bounds index!\n";
        return false;
    }

    out_node = this->sceneNodes[index];
    return true;
}
