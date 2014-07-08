#ifndef CLIENT_HPP
#define CLIENT_HPP

#include <enet/enet.h>
#include <iostream>

namespace mugg {
    namespace net {
        class Client {
            private:
                ENetAddress address;
                ENetHost* host;
                ENetEvent event;

                int maxConnections, maxChannels, incThrottle, outThrottle;
                bool initialized;
            public:
                Client();
                ~Client();
        };
    }
}

#endif
