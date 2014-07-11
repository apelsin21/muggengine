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

                bool Initialize(int maxChannels, unsigned int inLimit, unsigned int outLimit);
                
                bool IsConnected();

                bool Connect(const char* address, unsigned short port, int timeout);
                void Disconnect(int timeout);

                bool SendPacket(mugg::net::StringPacket packet, unsigned int channel);

                void PollEvents(int timeout);
        };
    }
}

#endif
