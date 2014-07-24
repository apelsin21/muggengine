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
    namespace net {
        class NetManager {
            private:
                std::vector<mugg::net::Client> clients;
                std::vector<mugg::net::Server> servers;
            
                std::vector<mugg::net::Client> clientQueue;
                std::vector<mugg::net::Server> serverQueue;
    
                std::vector<std::thread> threads;            

                bool running;
                void Poll();
            public:
                NetManager();
                ~NetManager();

                bool AddClient(mugg::net::Client&);
                bool GetClientByIndex(int, mugg::net::Client&);
                std::vector<mugg::net::Client> GetCurrentClients();
                int GetNumberOfClients();

                bool AddServer(mugg::net::Server&);
                bool GetServerByIndex(int, mugg::net::Server&);
                std::vector<mugg::net::Server> GetCurrentServers();
                int GetNumberOfServers();

                void Start();
                void Stop();
                void Break();
        };
    }
}

#endif
