#include "sprite.hpp"
#include "guimanager.hpp"

mugg::gui::Sprite::Sprite(mugg::gui::GUIManager* creator) : GUIObject(creator) {
    this->positionBottomLeft  = glm::vec3(-1.0f, -1.0f, 0.0f); 
    this->positionTopRight    = glm::vec3( 1.0f,  1.0f, 0.0f);
    this->positionTopLeft     = glm::vec3(-1.0f,  1.0f, 0.0f);
    this->positionBottomRight = glm::vec3( 1.0f, -1.0f, 0.0f);

    this->uvBottomLeft  = glm::vec2(0.0f, 0.0f); 
    this->uvTopRight    = glm::vec2(1.0f, 1.0f);
    this->uvTopLeft     = glm::vec2(0.0f, 1.0f);
    this->uvBottomRight = glm::vec2(1.0f, 0.0f);

    this->colorBottomLeft = glm::vec3(1.0f, 1.0f, 1.0f); 
    this->colorTopRight = glm::vec3(1.0f, 1.0f, 1.0f);
    this->colorTopLeft = glm::vec3(1.0f, 1.0f, 1.0f);
    this->colorBottomRight = glm::vec3(1.0f, 1.0f, 1.0f);

    this->positionChanged = true;
    this->colorChanged = true;
    this->uvChanged = true;
}
mugg::gui::Sprite::~Sprite() {
}

bool mugg::gui::Sprite::IsPositionChanged() {
    return this->positionChanged;
}
bool mugg::gui::Sprite::IsUVChanged() {
    return this->uvChanged;
}
bool mugg::gui::Sprite::IsColorChanged() {
    return this->colorChanged;
}

//POSITION SETTERS & GETTERS START 
glm::vec3 mugg::gui::Sprite::GetBottomLeftPosition() {
    this->positionChanged = false;
    return this->positionBottomLeft;
}
void mugg::gui::Sprite::SetBottomLeftPosition(const glm::vec3& pos) {
    this->positionChanged = true;
    this->positionBottomLeft = pos;
}
glm::vec3 mugg::gui::Sprite::GetTopLeftPosition() {
    this->positionChanged = false;
    return this->positionTopLeft;
}
void mugg::gui::Sprite::SetTopLeftPosition(const glm::vec3& pos) {
    this->positionChanged = true;
    this->positionTopLeft = pos;
}
glm::vec3 mugg::gui::Sprite::GetBottomRightPosition() {
    this->positionChanged = false;
    return this->positionBottomRight;
}
void mugg::gui::Sprite::SetBottomRightPosition(const glm::vec3& pos) {
    this->positionChanged = true;
    this->positionBottomRight = pos;
}
glm::vec3 mugg::gui::Sprite::GetTopRightPosition() {
    this->positionChanged = false;
    return this->positionTopRight;
}
void mugg::gui::Sprite::SetTopRightPosition(const glm::vec3& pos) {
    this->positionChanged = true;
    this->positionTopRight = pos;
}
//POSITION SETTERS & GETTERS END 

//UV SETTERS & GETTERS START
glm::vec2 mugg::gui::Sprite::GetBottomLeftUV() {
    this->uvChanged = false;
    return this->uvBottomLeft;
}
void mugg::gui::Sprite::SetBottomLeftUV(const glm::vec2& uv) {
    this->uvChanged = true;
    this->uvBottomLeft = uv;
}
glm::vec2 mugg::gui::Sprite::GetTopLeftUV() {
    this->uvChanged = false;
    return this->uvTopLeft;
}
void mugg::gui::Sprite::SetTopLeftUV(const glm::vec2& uv) {
    this->uvChanged = true;
    this->uvTopLeft = uv;
}
glm::vec2 mugg::gui::Sprite::GetBottomRightUV() {
    this->uvChanged = false;
    return this->uvBottomRight;
}
void mugg::gui::Sprite::SetBottomRightUV(const glm::vec2& uv) {
    this->uvChanged = true;
    this->uvBottomRight = uv;
}
glm::vec2 mugg::gui::Sprite::GetTopRightUV() {
    this->uvChanged = false;
    return this->uvTopRight;
}
void mugg::gui::Sprite::SetTopRightUV(const glm::vec2& uv) {
    this->uvChanged = true;
    this->uvTopRight = uv;
}
//UV SETTERS & GETTERS END 

//POSITION SETTERS & GETTERS START 
glm::vec3 mugg::gui::Sprite::GetBottomLeftColor() {
    this->colorChanged = false;
    return this->colorBottomLeft;
}
void mugg::gui::Sprite::SetBottomLeftColor(const glm::vec3& color) {
    this->colorChanged = true;
    this->colorBottomLeft = color;
}
glm::vec3 mugg::gui::Sprite::GetTopLeftColor() {
    this->colorChanged = false;
    return this->colorTopLeft;
}
void mugg::gui::Sprite::SetTopLeftColor(const glm::vec3& color) {
    this->colorChanged = true;
    this->colorTopLeft = color;
}
glm::vec3 mugg::gui::Sprite::GetBottomRightColor() {
    this->colorChanged = false;
    return this->colorBottomRight;
}
void mugg::gui::Sprite::SetBottomRightColor(const glm::vec3& color) {
    this->colorChanged = true;
    this->colorBottomRight = color;
}
glm::vec3 mugg::gui::Sprite::GetTopRightColor() {
    this->colorChanged = false;
    return this->colorTopRight;
}
void mugg::gui::Sprite::SetTopRightColor(const glm::vec3& color) {
    this->colorChanged = true;
    this->colorTopRight = color;
}
//POSITION SETTERS & GETTERS END 
