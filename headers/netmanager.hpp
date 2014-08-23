#ifndef NETMANAGER_HPP
#define NETMANAGER_HPP

#include <iostream>
#include <vector>
#include <thread>
#include <mutex>

#include "server.hpp"
#include "client.hpp"
#include "netdefs.hpp"

namespace mugg {
    namespace core {
        class Engine;
    }
    namespace net {
        struct ClientConnectCommand {
            const char* address;
            unsigned int timeout;
            unsigned int port;
            unsigned int index;
        };
        struct ClientDisconnectCommand {
            unsigned int timeout;
            unsigned int index;
        };

        class NetManager {
            private:
                std::vector<mugg::net::Client*> clients, clientQueue;
                std::vector<mugg::net::Server*> servers, serverQueue;

                std::vector<ClientConnectCommand> clientConnectQueue;
                std::vector<ClientDisconnectCommand> clientDisconnectQueue;

                mugg::core::Engine* parent;
                
                bool updateServers, updateClients;
                std::vector<std::thread> threads;
            public:
                NetManager(mugg::core::Engine*);
                ~NetManager();

                virtual mugg::net::Client* CreateClient();
                virtual std::size_t GetClientCount();
                virtual std::size_t GetClientQueueCount();

                virtual mugg::net::Server* CreateServer();
                virtual std::size_t GetServerCount();
                virtual std::size_t GetServerQueueCount();
        
                virtual void UpdateClients();
                virtual void UpdateServers();
        };
    }
}

#endif
