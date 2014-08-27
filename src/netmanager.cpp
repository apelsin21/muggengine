#include "netmanager.hpp"

mugg::net::NetManager::NetManager(mugg::core::Engine* parent) {
    this->parent = parent;
    
    for(unsigned int i = 0; i < this->threads.size(); i++) {
        this->threads[i].detach();
    }
}
mugg::net::NetManager::~NetManager() {
    this->updateClients = false;
    this->updateServers = false;

    for(unsigned int i = 0; i < this->clients.size(); i++) {
        if(this->clients[i] != nullptr) {
            delete this->clients[i];
        }
    }
    for(unsigned int i = 0; i < this->servers.size(); i++) {
        if(this->servers[i] != nullptr) {
            delete this->servers[i];
        }
    }

    for(unsigned int i = 0; i < this->threads.size(); i++) {
        if(this->threads[i].joinable()) {
            this->threads[i].join();
        }
    }
}

mugg::net::Client* mugg::net::NetManager::CreateClient() {
    mugg::net::Client* client = new mugg::net::Client(this);
    
    if(this->clients.empty() && this->clientQueue.empty()) {
        this->threads.push_back(std::thread(&mugg::net::NetManager::UpdateClients, this));
    }
    
    this->updateClients = true;

    this->clientQueue.push_back(client);

    return client;
}
std::size_t mugg::net::NetManager::GetClientCount() {
    return this->clients.size();
}
std::size_t mugg::net::NetManager::GetClientQueueCount() {
    return this->clientQueue.size();
}

mugg::net::Server* mugg::net::NetManager::CreateServer() {
    mugg::net::Server* server = new mugg::net::Server(this);

    if(this->servers.empty() && this->serverQueue.empty()) {
        this->threads.push_back(std::thread(&mugg::net::NetManager::UpdateServers, this));
    }

    this->updateServers = true;
    
    this->serverQueue.push_back(server);

    return server;
}
std::size_t mugg::net::NetManager::GetServerCount() {
    return this->servers.size();
}
std::size_t mugg::net::NetManager::GetServerQueueCount() {
    return this->serverQueue.size();
}

void mugg::net::NetManager::UpdateClients() {
    while(this->updateClients) {
        if(!this->clientQueue.empty()) {
            for(unsigned int i = 0; i < this->clientQueue.size(); i++) {
                this->clients.push_back(this->clientQueue[i]);
                this->clientQueue.erase(this->clientQueue.begin() + i);
                i--;
            }
        }
        
        if(!this->clients.empty()) {
            for(unsigned int i = 0; i < this->clients.size(); i++) {
                this->clients[i]->Poll(200);
            }
            
            if(!this->clientConnectQueue.empty()) {
                for(unsigned int i = 0; i < this->clientConnectQueue.size(); i++) {
                    this->clients[this->clientConnectQueue[i].index]->Connect(this->clientConnectQueue[i].address, this->clientConnectQueue[i].port, this->clientConnectQueue[i].timeout);
                    this->clientConnectQueue.erase(this->clientConnectQueue.begin() + i);
                    i--;
                }
            }
            
            if(!this->clientDisconnectQueue.empty()) {
                for(unsigned int i = 0; i < this->clientDisconnectQueue.size(); i++) {
                    this->clients[this->clientDisconnectQueue[i].index]->Disconnect(this->clientConnectQueue[i].timeout);
                    this->clientDisconnectQueue.erase(this->clientDisconnectQueue.begin() + i);
                    i--;
                }
            }
        }
    }
}
void mugg::net::NetManager::UpdateServers() {
    while(this->updateServers) {
        if(!this->serverQueue.empty()) {
            for(unsigned int i = 0; i < this->serverQueue.size(); i++) {
                this->servers.push_back(this->serverQueue[i]);
                this->serverQueue.erase(this->serverQueue.begin() + i);
                i--;
            }
        }
        
        if(!this->servers.empty()) {
            for(unsigned int i = 0; i < this->servers.size(); i++) {
                this->servers[i]->Poll(200);
            }
        }
    }
}
