#ifndef SERVER_HPP
#define SERVER_HPP

#include <iostream>
#include <vector>
#include <stdio.h>

#include <enet/enet.h>

#include "client.hpp"

#include "netbase.hpp"

namespace mugg {
    namespace net {
        class Server : public NetBase {
            private:
                std::vector<ENetAddress> connectedClients;
                unsigned int numberOfClients;
            public:
                Server(mugg::net::NetManager*);
                ~Server();

                bool Initialize(const char* address, unsigned short port, int maxConnections, int maxChannels, unsigned int inLimit, unsigned int outLimit);
                bool Initialize(unsigned short port);
                
                std::string GetClientAddressByIndex(unsigned int index);
                unsigned short GetClientPortByIndex(unsigned int index);

                unsigned int GetNumberOfClients();

                void DisconnectAllClients();
                void DisconnectClient();
    
                void Poll(unsigned int);
        };
    }
}

#endif
