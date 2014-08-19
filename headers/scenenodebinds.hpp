#ifndef SCENENODEBINDS_HPP
#define SCENENODEBINDS_HPP

#include <lua.hpp>

#include <glm/glm.hpp>

#include "scenenode.hpp"
#include "meshbinds.hpp"
#include "vec4binds.hpp"

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

        int sceneNodeSetPosition(lua_State* L) {
            mugg::scene::SceneNode* node = checkSceneNode(L, 1);
            glm::vec4* position = checkvec4(L, 2);

            node->SetPosition(*position);

            return 0;
        }

        luaL_Reg sceneNodeFuncs[] = {
            {"add_mesh", sceneNodeAddMesh},
         
            {"set_position", sceneNodeSetPosition},

            {NULL, NULL},
        };
    }
}

#endif
