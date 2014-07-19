#ifndef NETMANAGERBINDS_HPP
#define NETMANAGERBINDS_HPP

#include "netmanager.hpp"
#include "server.hpp"
#include "client.hpp"
#include "netdefs.hpp"
#include "serverbinds.hpp"
#include "clientbinds.hpp"

#include <lua.hpp>

namespace mugg {
    namespace binds {
        static const char* NetManagerPrivateName = "mugg_NetManager";
        static const char* NetManagerPublicName = "NetManager";
    
        mugg::net::NetManager* checkNetManager(lua_State* L, int n) {
            return *(mugg::net::NetManager**)luaL_checkudata(L, n, NetManagerPrivateName);
        }

        int netManagerConstructor(lua_State* L) {
            mugg::net::NetManager** netMgr = (mugg::net::NetManager**)lua_newuserdata(L, sizeof(mugg::net::NetManager*));
            *netMgr = new mugg::net::NetManager();

            luaL_getmetatable(L, NetManagerPrivateName);
            lua_setmetatable(L, -2);
           
            return 1;
        }
        int netManagerDeconstructor(lua_State* L) {
            mugg::net::NetManager* netMgr = checkNetManager(L, 1);

            delete netMgr;

            return 0;
        }

        int netManagerAddClient(lua_State* L) {
            mugg::net::NetManager* netMgr = checkNetManager(L, 1);
            mugg::net::Client* client = checkClient(L, 2);

            netMgr->AddClient(*client);

            return 0;
        }
        int netManagerGetClientByIndex(lua_State* L) {
            mugg::net::NetManager* netMgr = checkNetManager(L, 1);

            
        }

        luaL_Reg netManagerFuncs[] = {
            {"new", netManagerConstructor},
            
            {"__gc", netManagerDeconstructor},
            {NULL, NULL}
        };
    }
}

#endif
