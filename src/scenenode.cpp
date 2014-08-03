#include "scenenode.hpp"

mugg::scene::SceneNode::SceneNode(mugg::scene::SceneManager* parent) {
    this->parent = parent;
}
mugg::scene::SceneNode::~SceneNode() {
}
