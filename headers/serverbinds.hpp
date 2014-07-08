#ifndef SERVERBINDS_HPP
#define SERVERBINDS_HPP

#include <lua.hpp>
#include <iostream>

#include "server.hpp"

namespace mugg {
    namespace binds {
        static const char* ServerPrivateName = "mugg_Server";
        static const char* ServerPublicName = "Server";

        mugg::net::Server* checkServer(lua_State* L, int n) {
            return *(mugg::net::Server**)luaL_checkudata(L, n, ServerPrivateName);
        }

        int serverConstructor(lua_State* L) {
            mugg::net::Server** server = (mugg::net::Server**)lua_newuserdata(L, sizeof(mugg::net::Server*));
            *server = new mugg::net::Server();

            luaL_getmetatable(L, ServerPrivateName);
            lua_setmetatable(L, -2);

            return 1;
        }

        int serverDeconstructor(lua_State* L) {
            mugg::net::Server* server = checkServer(L, 1);

            delete server;

            return 0;
        }

        int serverInitialize(lua_State* L) {
            mugg::net::Server* server = checkServer(L, 1);

            const char* address = luaL_checkstring(L, 2);
            unsigned short port = (unsigned short)luaL_checknumber(L, 3);
            int maxConnections = luaL_checknumber(L, 4);
            int maxChannels = luaL_checknumber(L, 5);
            int incThrottle = luaL_checknumber(L, 6);
            int outThrottle = luaL_checknumber(L, 7);

            server->Initialize(address, port, maxConnections, maxChannels, incThrottle, outThrottle);

            return 0;
        }

        int serverInitializeMinimal(lua_State* L) {
            mugg::net::Server* server = checkServer(L, 1);

            unsigned short port = (unsigned short)luaL_checknumber(L, 2);

            server->Initialize(port);

            return 0;
        }

        int serverPollEvents(lua_State* L) {
            mugg::net::Server* server = checkServer(L, 1);

            int timeout = luaL_checknumber(L, 2);

            server->PollEvents(timeout);

            return 0;
        }

        int serverGetMaxConnections(lua_State* L) {
            mugg::net::Server* server = checkServer(L, 1);

            lua_pushnumber(L, server->GetMaxConnections());

            return 1;
        }
        int serverGetMaxChannels(lua_State* L) {
            mugg::net::Server* server = checkServer(L, 1);

            lua_pushnumber(L, server->GetMaxChannels());

            return 1;
        }
        int serverGetIncThrottle(lua_State* L) {
            mugg::net::Server* server = checkServer(L, 1);

            lua_pushnumber(L, server->GetIncThrottle());

            return 1;
        }
        int serverGetOutThrottle(lua_State* L) {
            mugg::net::Server* server = checkServer(L, 1);

            lua_pushnumber(L, server->GetOutThrottle());

            return 1;
        }
        int serverIsInitialized(lua_State* L) {
            mugg::net::Server* server = checkServer(L, 1);

            lua_pushboolean(L, server->IsInitialized());

            return 1;
        }

        luaL_Reg serverFuncs[] = {
            {"new", serverConstructor},

            {"initialize", serverInitialize},
            {"initialize", serverInitializeMinimal},

            {"get_max_connections", serverGetMaxConnections},
            {"get_max_channels", serverGetMaxChannels},
            {"get_in_throttle", serverGetIncThrottle},
            {"get_out_throttle", serverGetOutThrottle},
            {"is_initialized", serverIsInitialized},

            {"poll", serverPollEvents},

            {"__gc", serverDeconstructor},
            {NULL, NULL}
        };
    }
}

#endif
