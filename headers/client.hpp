#ifndef CLIENT_HPP
#define CLIENT_HPP

#include <enet/enet.h>
#include <iostream>

#include "netbase.hpp"
#include "stringpacket.hpp"

namespace mugg {
    namespace net {
        class Client : public NetBase {
            private:
                ENetPeer* peer;

                bool connected;
            public:
                Client();
                ~Client();

                bool Initialize(int, unsigned int, unsigned int);
                bool Initialize();

                bool IsConnected();

                bool Connect(const char*, unsigned short, int);
                void Disconnect(int);

                bool SendPacket(mugg::net::StringPacket, unsigned int);

                void PollEvents(int);
        };
    }
}

#endif
