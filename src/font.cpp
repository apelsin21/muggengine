#include "font.hpp"

mugg::gui::Font::Font(mugg::gui::GUIManager* parent) {
    this->parent = parent;
}
mugg::gui::Font::~Font() {
}

bool mugg::gui::Font::Load(const std::string& filepath, int pixelSize = 48) {
    FT_Library ft;

    if(FT_Init_FreeType(&ft)) {
        std::cout << "Failed to initialize FreeType2!\n";
        return false;
    }

    FT_Face face;

    if(FT_New_Face(ft, filepath.c_str(), 0, &face)) {
        std::cout << "FreeType2 failed to open font " << filepath << std::endl;
        return false;
    }

    FT_Set_Pixel_Sizes(face, 0, pixelSize);

    FT_GlyphSlot g = face->glyph;
    int w = 0, h = 0;

    for(unsigned int i = 32; i < 128; i++) {
        if(FT_Load_Char(face, i, FT_LOAD_RENDER)) {
            std::cout << "FreeType2 failed loading character " << i << std::endl;
            continue;
        }

        w += g->bitmap.width;
        h = std::max(h, g->bitmap.rows);

        int atlas_width = w;
    }
}
