#ifndef SCENEMANAGERBINDS_HPP
#define SCENEMANAGERBINDS_HPP

#include <lua.hpp>

#include "scenemanager.hpp"
#include "scenenodebinds.hpp"

namespace mugg {
    namespace binds {
        static const char* SceneManagerName = "SceneManager";

        mugg::scene::SceneManager* checkSceneManager(lua_State* L, int n) {
            return *(mugg::scene::SceneManager**)luaL_checkudata(L, n, SceneManagerName);
        }

        int sceneManagerCreateNode(lua_State* L) {
            mugg::scene::SceneManager* mgr = checkSceneManager(L, 1);

            mugg::scene::SceneNode** node = (mugg::scene::SceneNode**)lua_newuserdata(L, sizeof(mugg::scene::SceneNode*));
            *node = mgr->CreateSceneNode();

            luaL_getmetatable(L, SceneNodeName);
            lua_setmetatable(L, -2);

            return 1;
        }

        luaL_Reg sceneManagerFuncs[] = {
            {"create_node", sceneManagerCreateNode},

            {NULL, NULL},
        };
    }
}

#endif
