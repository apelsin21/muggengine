#include "scenenode.hpp"

mugg::scene::SceneNode::SceneNode(mugg::scene::SceneManager* parent) {
    this->parent = parent;
}
mugg::scene::SceneNode::~SceneNode() {
}

void mugg::scene::SceneNode::AddMesh(mugg::graphics::Mesh*& mesh) {
    this->meshes.push_back(mesh);
}
bool mugg::scene::SceneNode::GetMeshByIndex(int index, mugg::graphics::Mesh*& out_mesh) {
    if(index < 0 || index > this->meshes.size() || this->meshes.empty()) {
        return false;
    }

    out_mesh = this->meshes[index];
    return true;
}
int mugg::scene::SceneNode::GetNumberOfMeshes() {
    return this->meshes.size();
}

void mugg::scene::SceneNode::SetPosition(const glm::vec4& in_position) {
    this->position = position;
}
glm::vec4 mugg::scene::SceneNode::GetPosition() {
    return this->position;
}
