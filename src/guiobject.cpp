#include "guiobject.hpp"

mugg::gui::GUIObject::GUIObject(mugg::gui::GUIManager* parent, unsigned int index) {
    this->parent = parent;
    this->index = index;
    this->rotationAngle = 0.0f;
    this->rotation = glm::vec2(1.0f, 1.0f);
    this->scale = glm::vec2(1.0f, 1.0f);
}
mugg::gui::GUIManager* mugg::gui::GUIObject::GetParent() {
    return this->parent;
}

void mugg::gui::GUIObject::SetScale(const glm::vec2& scale) {
    this->scale = scale;
}
glm::vec2 mugg::gui::GUIObject::GetScale() {
    return this->scale;
}

void mugg::gui::GUIObject::SetRotation(const glm::vec2& rotation) {
    this->rotation = rotation;
}
glm::vec2 mugg::gui::GUIObject::GetRotation() {
    return this->rotation;
}

void mugg::gui::GUIObject::SetRotationAngle(float angle) {
    this->rotationAngle = angle;
}
float mugg::gui::GUIObject::GetRotationAngle() {
    return this->rotationAngle;
}

void mugg::gui::GUIObject::SetPosition(const glm::vec2& position) {
    this->position = position;
}
glm::vec2 mugg::gui::GUIObject::GetPosition() {
    return this->position;
}

void mugg::gui::GUIObject::SetTexture(mugg::graphics::Texture2D* texture) {
    this->texture = texture;
}
mugg::graphics::Texture2D* mugg::gui::GUIObject::GetTexture() {
    return this->texture;

}

unsigned int mugg::gui::GUIObject::GetIndex() {
    return this->index;
}
