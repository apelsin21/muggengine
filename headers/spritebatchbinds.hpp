#ifndef SPRITEBATCHBINDS_HPP
#define SPRITEBATCHBINDS_HPP

#include <lua.hpp>

#include "spritebatch.hpp"
#include "spritebinds.hpp"
#include "texture2dbinds.hpp"

namespace mugg {
    namespace binds {
        static const char* SpriteBatchName = "SpriteBatch";

        mugg::gui::SpriteBatch* checkSpriteBatch(lua_State* L, int n) {
            return *(mugg::gui::SpriteBatch**)luaL_checkudata(L, n, SpriteBatchName);
        }

        int spriteBatchAddSprite(lua_State* L) {
            mugg::gui::SpriteBatch* batch = checkSpriteBatch(L, 1);
            mugg::gui::Sprite* sprite = checkSprite(L, 2);

            batch->AddSprite(sprite);

            return 0;
        }
        
        
        int spriteBatchSetTexture(lua_State* L) {
            mugg::gui::SpriteBatch* batch = checkSpriteBatch(L, 1);
            mugg::graphics::Texture2D* texture = checkTexture2D(L, 2);

            batch->SetTextureID(texture->GetID());

            return 0;
        }
        
        int spriteBatchRender(lua_State* L) {
            mugg::gui::SpriteBatch* batch = checkSpriteBatch(L, 1);

            batch->Render();

            return 0;
        }


        luaL_Reg spriteBatchFuncs[] = {
            {"add_sprite", spriteBatchAddSprite},
            
            {"set_texture", spriteBatchSetTexture},

            {"render", spriteBatchRender},

            {NULL, NULL}
        };
    }
}

#endif
