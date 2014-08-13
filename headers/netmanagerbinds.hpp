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
        static const char* NetManagerName = "NetManager";
    
        mugg::net::NetManager* checkNetManager(lua_State* L, int n) {
            return *(mugg::net::NetManager**)luaL_checkudata(L, n, NetManagerName);
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
            {NULL, NULL}
        };
    }
}

#endif
