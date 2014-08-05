#ifndef SCENENODEBINDS_HPP
#define SCENENODEBINDS_HPP

#include <lua.hpp>

#include "scenenode.hpp"
#include "meshbinds.hpp"

namespace mugg {
    namespace binds {
        static const char* SceneNodeName = "SceneNode";

        mugg::scene::SceneNode* checkSceneNode(lua_State* L, int n) {
            return *(mugg::scene::SceneNode**)luaL_checkudata(L, n, SceneNodeName);
        }

        int sceneNodeAddMesh(lua_State* L) {
            mugg::scene::SceneNode* node = checkSceneNode(L, 1);
            mugg::graphics::Mesh* mesh = checkMesh(L, 2);

            node->AddMesh(mesh);

            return 0;
        }

        luaL_Reg sceneNodeFuncs[] = {
            {"add_mesh", sceneNodeAddMesh},
            
            {NULL, NULL},
        };
    }
}

#endif
