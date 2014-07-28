#include "guiobject.hpp"

mugg::gui::GUIObject::GUIObject(mugg::gui::GUIManager* creator, unsigned int index) {
    this->creator = creator;
    this->index = index;
}
mugg::gui::GUIManager* mugg::gui::GUIObject::GetCreator() {
    return this->creator;
}

void mugg::gui::GUIObject::SetPosition(glm::vec2 position) {
    this->creator->SetObjectPosition(this->index, position);
}
glm::vec2 mugg::gui::GUIObject::GetPosition() {
    return this->creator->GetObjectPosition(this->index);
}

void mugg::gui::GUIObject::SetTexture(GLuint texture) {
    this->creator->SetObjectTexture(this->index, texture);
}
GLuint mugg::gui::GUIObject::GetTexture() {
    return this->creator->GetObjectTexture(this->index);

}

unsigned int mugg::gui::GUIObject::GetIndex() {
    return this->index;
}
