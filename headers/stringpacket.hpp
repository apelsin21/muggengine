#ifndef STRINGPACKET_HPP
#define STRINGPACKET_HPP

#include "packetbase.hpp"
#include "netdefs.hpp"

#include <string.h>

namespace mugg {
    namespace net {
        class StringPacket : public PacketBase {
            private:
                const char* data;
            public:
                StringPacket();
                StringPacket(const char*, mugg::net::PacketFlag);

                void SetData(const char*, mugg::net::PacketFlag);
                void AppendData(const char*);
                void Truncate(std::size_t);
                const char* GetData();
        };
    }
}

#endif
