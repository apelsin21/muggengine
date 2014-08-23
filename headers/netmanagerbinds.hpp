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


        int netManagerCreateClient(lua_State* L) {
            mugg::net::NetManager* netMgr = checkNetManager(L, 1);
            
            mugg::net::Client** client = (mugg::net::Client**)lua_newuserdata(L, sizeof(mugg::net::Client*));
            *client = netMgr->CreateClient();

            luaL_getmetatable(L, ClientName);
            lua_setmetatable(L, -2);

            return 1;
        }
        int netManagerCreateServer(lua_State* L) {
            mugg::net::NetManager* netMgr = checkNetManager(L, 1);
            
            mugg::net::Server** server = (mugg::net::Server**)lua_newuserdata(L, sizeof(mugg::net::Server*));
            *server = netMgr->CreateServer();

            luaL_getmetatable(L, ServerName);
            lua_setmetatable(L, -2);
        
            return 1; 
        }

        int netManagerGetClientCount(lua_State* L) {
            mugg::net::NetManager* mgr = checkNetManager(L, 1);

            lua_pushnumber(L, mgr->GetClientCount());

            return 1;
        }
        int netManagerGetClientQueueCount(lua_State* L) {
            mugg::net::NetManager* mgr = checkNetManager(L, 1);

            lua_pushnumber(L, mgr->GetClientQueueCount());

            return 1;
        }

        luaL_Reg netManagerFuncs[] = {
            {"create_client", netManagerCreateClient},
            {"create_server", netManagerCreateServer},

            {"get_client_count", netManagerGetClientCount},
            {"get_client_queue_count", netManagerGetClientQueueCount},

            {NULL, NULL}
        };
    }
}

#endif
