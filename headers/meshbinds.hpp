#ifndef MESHBINDS_HPP
#define MESHBINDS_HPP

#include "mesh.hpp"
#include "texture2d.hpp"
#include "texture2dbinds.hpp"

#include <lua.hpp>

namespace mugg {
    namespace binds {
        static const char* MeshName = "Mesh";
    
        mugg::graphics::Mesh* checkMesh(lua_State* L, int n) {
            return *(mugg::graphics::Mesh**)luaL_checkudata(L, n, MeshName);
        }

        int meshGetFilepath(lua_State* L) {
            mugg::graphics::Mesh* mesh = checkMesh(L, 1);

            lua_pushstring(L, mesh->GetFilepath().c_str());

            return 1;
        }

        int meshGetNumberOfVertices(lua_State* L) {
            mugg::graphics::Mesh* mesh = checkMesh(L, 1);

            lua_pushnumber(L, mesh->GetNumberOfVertices());
            
            return 1;
        }
        int meshGetNumberOfIndices(lua_State* L) {
            mugg::graphics::Mesh* mesh = checkMesh(L, 1);

            lua_pushnumber(L, mesh->GetNumberOfIndices());
            
            return 1;
        }
        int meshGetNumberOfUVS(lua_State* L) {
            mugg::graphics::Mesh* mesh = checkMesh(L, 1);

            lua_pushnumber(L, mesh->GetNumberOfUVS());

            return 1;
        }
        int meshGetNumberOfNormals(lua_State* L) {
            mugg::graphics::Mesh* mesh = checkMesh(L, 1);

            lua_pushnumber(L, mesh->GetNumberOfNormals());

            return 1;
        }

        int meshSetTexture2D(lua_State* L) {
            mugg::graphics::Mesh* mesh = checkMesh(L, 1);
            mugg::graphics::Texture2D* texture = checkTexture2D(L, 2);

            mesh->SetTexture(texture);

            return 0;
        }

        luaL_Reg meshFuncs[] = {
            {"set_texture2d", meshSetTexture2D},

            {"get_filepath", meshGetFilepath},

            {"get_number_of_vertices", meshGetNumberOfVertices},
            {"get_number_of_indices", meshGetNumberOfIndices},
            {"get_number_of_uvs", meshGetNumberOfUVS},
            {"get_number_of_normals", meshGetNumberOfNormals},

            {NULL, NULL},
        };
    }
}

#endif
