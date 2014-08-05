#include "scenenode.hpp"

mugg::scene::SceneNode::SceneNode(mugg::scene::SceneManager* parent) {
    this->parent = parent;
}
mugg::scene::SceneNode::~SceneNode() {
}

void mugg::scene::SceneNode::AddMesh(mugg::graphics::Mesh*& mesh) {
    this->meshes.push_back(mesh);
}
std::size_t mugg::scene::SceneNode::GetNumberOfMeshes() {
    return this->meshes.size();
}
