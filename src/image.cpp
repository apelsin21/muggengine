#include "image.hpp"
#include "guimanager.hpp"

mugg::gui::Image::Image(mugg::gui::GUIManager* creator, unsigned int index) : GUIObject(creator, index) {
    this->spriteBatchIndex = 0;
}
mugg::gui::Image::~Image() {
}

unsigned int mugg::gui::Image::GetSpriteBatchIndex() {
    return this->spriteBatchIndex;
}
void mugg::gui::Image::SetSpriteBatchIndex(unsigned int index) {
    this->spriteBatchIndex = index;
}
