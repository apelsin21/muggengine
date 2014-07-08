#ifndef SERVER_HPP
#define SERVER_HPP

#include <iostream>

#include <enet/enet.h>

namespace mugg {
    namespace net {
        class Server {
            private:
                ENetAddress address;
                ENetHost* host;
                ENetEvent event;

                int maxConnections, maxChannels, incThrottle, outThrottle;
                bool initialized;
            public:
                Server();
                ~Server();

                bool Initialize(const char* address, unsigned short port, int maxConnections, int maxChannels, int incThrottle, int outThrottle);
                bool Initialize(unsigned short port);

                int GetMaxConnections();
                int GetMaxChannels();
                int GetIncThrottle();
                int GetOutThrottle();
                bool IsInitialized();

                void PollEvents(int timeout);
        };
    }
}

#endif
