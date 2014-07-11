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
                StringPacket(const char* data, mugg::net::PacketFlag flag);

                void SetData(const char* data, mugg::net::PacketFlag flag);
                void AppendData(const char* data);
                void Truncate(std::size_t size);
                const char* GetData();
        };
    }
}

#endif
