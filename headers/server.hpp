#ifndef SERVER_HPP
#define SERVER_HPP

#include <iostream>
#include <vector>

#include <enet/enet.h>

#include "client.hpp"

#include "netbase.hpp"

namespace mugg {
    namespace net {
        class Server : public NetBase {
            private:
                std::vector<ENetAddress> connectedClients;
                int numberOfClients;
            public:
                Server();
                ~Server();

                bool Initialize(const char* address, unsigned short port, int maxConnections, int maxChannels, int incThrottle, int outThrottle);
                bool Initialize(unsigned short port);
                
                const char* GetClientAddressByIndex(unsigned int index);
                unsigned short GetClientPortByIndex(unsigned int index);

                int GetNumberOfClients();

                void PollEvents(int timeout);
        };
    }
}

#endif
