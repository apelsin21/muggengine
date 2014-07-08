#ifndef CLIENTBINDS_HPP
#define CLIENTBINDS_HPP

#include <lua.hpp>

#include "client.hpp"

namespace mugg {
    namespace binds {
        static const char* ClientPrivateName = "mugg_Client";
        static const char* ClientPublicName = "Client";

        mugg::net::Client* checkClient(lua_State* L, int n) {
            return *(mugg::net::Client**)luaL_checkudata(L, n, ClientPrivateName);
        }

        int clientConstructor(lua_State* L) {
            mugg::net::Client** client = (mugg::net::Client**)lua_newuserdata(L, sizeof(mugg::net::Client*));
            *client = new mugg::net::Client();

            luaL_getmetatable(L, ClientPrivateName);
            lua_setmetatable(L, -2);

            return 1;
        }

        int clientDeconstructor(lua_State* L) {
            mugg::net::Client* client = checkClient(L, 1);

            delete client;

            return 0;
        }

        int clientInitialize(lua_State* L) {
            mugg::net::Client* client = checkClient(L, 1);

            int maxChannels = luaL_checknumber(L, 2);
            int incThrottle = luaL_checknumber(L, 3);
            int outThrottle = luaL_checknumber(L, 4);

            client->Initialize(maxChannels, incThrottle, outThrottle);

            return 0;
        }

        int clientConnect(lua_State* L) {
            mugg::net::Client* client = checkClient(L, 1);

            const char* address = luaL_checkstring(L, 2);
            unsigned short port = (unsigned short)luaL_checknumber(L, 3);
            int timeout = luaL_checknumber(L, 4);

            client->Connect(address, port, timeout);

            return 0;
        }

        int clientDisconnect(lua_State* L) {
            mugg::net::Client* client = checkClient(L, 1);

            int timeout = luaL_checknumber(L, 2);

            client->Disconnect(timeout);

            return 0;
        }

        int clientPollEvents(lua_State* L) {
            mugg::net::Client* client = checkClient(L, 1);

            int timeout = luaL_checknumber(L, 2);

            client->PollEvents(timeout);

            return 0;
        }

        int clientIsConnected(lua_State* L) {
            mugg::net::Client* client = checkClient(L, 1);

            lua_pushboolean(L, client->IsConnected());

            return 1;
        }

        luaL_Reg clientFuncs[] = {
            {"new", clientConstructor},

            {"initialize", clientInitialize},
            
            {"connect", clientConnect},
            {"disconnect", clientDisconnect},

            {"is_connected", clientIsConnected},

            {"poll", clientPollEvents},

            {"__gc", clientDeconstructor},
            {NULL, NULL}
        };
    }
}

#endif
