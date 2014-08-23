#ifndef CLIENT_HPP
#define CLIENT_HPP

#include <enet/enet.h>
#include <iostream>

#include "netbase.hpp"
#include "stringpacket.hpp"

namespace mugg {
    namespace net {
        class NetManager;

        class Client : public NetBase {
            private:
                ENetPeer* peer;

                bool connected;
            public:
                Client(mugg::net::NetManager*);
                ~Client();

                bool Initialize(int, unsigned int, unsigned int);
                bool Initialize();

                bool IsConnected();

                bool Connect(const char*, unsigned short, int);
                void Disconnect(int);

                bool SendPacket(mugg::net::StringPacket, unsigned int);

                std::string GetPeerAddress();

                void Poll();
        };
    }
}

#endif
