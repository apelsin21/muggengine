#ifndef STRINGPACKETBINDS_HPP
#define STRINGPACKETBINDS_HPP

#include <lua.hpp>

#include "netdefs.hpp"
#include "stringpacket.hpp"

namespace mugg {
    namespace binds {
        static const char* StringPacketName = "StringPacket";

        mugg::net::StringPacket* checkStringPacket(lua_State* L, int n) {
            return *(mugg::net::StringPacket**)luaL_checkudata(L, n, StringPacketName);
        }

        int stringPacketConstructor(lua_State* L) {
            mugg::net::StringPacket** packet = (mugg::net::StringPacket**)lua_newuserdata(L, sizeof(mugg::net::StringPacket*));
            *packet = new mugg::net::StringPacket();

            luaL_getmetatable(L, StringPacketName);
            lua_setmetatable(L, -2);


            return 1;
        }

        int stringPacketDeconstructor(lua_State* L) {
            mugg::net::StringPacket* packet = checkStringPacket(L, 1);

            delete packet;

            return 0;
        }

        int stringPacketSetData(lua_State* L) {
            mugg::net::StringPacket* packet = checkStringPacket(L, 1);

            const char* data = luaL_checkstring(L, 2);
            mugg::net::PacketFlag flag = (mugg::net::PacketFlag)luaL_checkoption(L, 3, NULL, mugg::net::PacketFlagString);
            
            packet->SetData(data, flag);

            return 0;
        }

        int stringPacketAppendData(lua_State* L) {
            mugg::net::StringPacket* packet = checkStringPacket(L, 1);

            const char* data = luaL_checkstring(L, 2);

            packet->AppendData(data);

            return 0;
        }

        int stringPacketTruncate(lua_State* L) {
            mugg::net::StringPacket* packet = checkStringPacket(L, 1);

            std::size_t size = luaL_checknumber(L, 2);

            packet->Truncate(size);

            return 0;
        }

        int stringPacketGetData(lua_State* L) {
            mugg::net::StringPacket* packet = checkStringPacket(L, 1);

            lua_pushstring(L, packet->GetData());

            return 1;
        }

        luaL_Reg stringPacketFuncs[] = {
            {"new", stringPacketConstructor},

            {"set_data", stringPacketSetData},
            {"get_data", stringPacketGetData},
            {"append_data", stringPacketAppendData},
            {"truncate", stringPacketTruncate},

            {"__gc", stringPacketDeconstructor},
            {NULL, NULL},
        };
    }
}

#endif
