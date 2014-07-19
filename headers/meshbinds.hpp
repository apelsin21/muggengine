#ifndef MESHBINDS_HPP
#define MESHBINDS_HPP

#include "mesh.hpp"
#include "texture2d.hpp"
#include "texture2dbinds.hpp"

#include <lua.hpp>

namespace mugg {
    namespace binds {
        static const char* MeshPrivateName = "mugg_Mesh";
        static const char* MeshPublicName = "Mesh";
    
        mugg::graphics::Mesh* checkMesh(lua_State* L, int n) {
            return *(mugg::graphics::Mesh**)luaL_checkudata(L, n, MeshPrivateName);
        }

        int meshConstructor(lua_State* L) {
            mugg::graphics::Mesh** mesh = (mugg::graphics::Mesh**)lua_newuserdata(L, sizeof(mugg::graphics::Mesh*));
            *mesh = new mugg::graphics::Mesh();

            luaL_getmetatable(L, MeshPrivateName);
            lua_setmetatable(L, -2);

            return 1;
        }
        int meshConstructorWithParams(lua_State* L) {
            const char* path = luaL_checkstring(L, 1);

            mugg::graphics::Mesh** mesh = (mugg::graphics::Mesh**)lua_newuserdata(L, sizeof(mugg::graphics::Mesh*));
            *mesh = new mugg::graphics::Mesh(path);

            luaL_getmetatable(L, MeshPrivateName);
            lua_setmetatable(L, -2);

            return 1;
        }
        int meshDeconstructor(lua_State* L) {
            mugg::graphics::Mesh* mesh = checkMesh(L, 1);

            delete mesh;

            return 0;
        }

        int meshLoad(lua_State* L) {
            mugg::graphics::Mesh* mesh = checkMesh(L, 1);

            const char* filepath = luaL_checkstring(L, 2);

            mesh->Load(filepath);

            return 0;
        }
        int meshGetFilepath(lua_State* L) {
            mugg::graphics::Mesh* mesh = checkMesh(L, 1);

            lua_pushstring(L, mesh->GetFilepath().c_str());

            return 1;
        }

        int meshAddTexture(lua_State* L) {
            mugg::graphics::Mesh* mesh = checkMesh(L, 1);
            mugg::graphics::Texture2D* texture = checkTexture2D(L, 2);

            mesh->AddTexture(*texture);
            
            return 0;
        }

        int meshGetNumberOfTextures(lua_State* L) {
            mugg::graphics::Mesh* mesh = checkMesh(L, 1);

            lua_pushnumber(L, mesh->GetNumberOfTextures());

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

        luaL_Reg meshFuncs[] = {
            {"new", meshConstructor},
            {"new", meshConstructorWithParams},

            {"load", meshLoad},
            {"get_filepath", meshGetFilepath},

            {"get_number_of_textures", meshGetNumberOfTextures},
            {"get_number_of_vertices", meshGetNumberOfVertices},
            {"get_number_of_indices", meshGetNumberOfIndices},
            {"get_number_of_uvs", meshGetNumberOfUVS},
            {"get_number_of_normals", meshGetNumberOfNormals},

            {"__gc", meshDeconstructor},
            {NULL, NULL},
        };
    }
}

#endif
