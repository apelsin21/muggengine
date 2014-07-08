#ifndef SERVER_HPP
#define SERVER_HPP

#include <iostream>
#include <enet/enet.h>

#include "netbase.hpp"

namespace mugg {
    namespace net {
        class Server : public NetBase {
            private:
            public:
                Server();
                ~Server();

                bool Initialize(const char* address, unsigned short port, int maxConnections, int maxChannels, int incThrottle, int outThrottle);
                bool Initialize(unsigned short port);

                void PollEvents(int timeout);
        };
    }
}

#endif
