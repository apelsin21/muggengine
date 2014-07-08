#ifndef CLIENT_HPP
#define CLIENT_HPP

#include <enet/enet.h>
#include <iostream>

#include "netbase.hpp"

namespace mugg {
    namespace net {
        class Client : public NetBase {
            private:
                ENetPeer* peer;

                bool connected;
            public:
                Client();
                ~Client();

                bool Initialize(int maxChannels, int incThrottle, int outThrottle);
                
                bool IsConnected();

                bool Connect(const char* address, unsigned short port, int timeout);
                void Disconnect(int timeout);

                void PollEvents(int timeout);
        };
    }
}

#endif
