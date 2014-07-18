#include "netmanager.hpp"

mugg::net::NetManager::NetManager() {
    this->running = false;

}
mugg::net::NetManager::~NetManager() {
    this->Break();
}

bool mugg::net::NetManager::AddClient(mugg::net::Client client) {
    if(!client.IsConnected() || !client.IsInitialized()) {
        std::cout << "Tried to add unconnected or unintialized client to netmanager!\n";
        return false;
    }
    
    this->clientQueue.push_back(client);
    
    return true;
}
bool mugg::net::NetManager::GetClientByIndex(int index, mugg::net::Client &out_client) {
    if(this->clients.size() != 0 && index <= this->clients.size()) {
        out_client = this->clients[index];
        return true;
    }

    return false;
}
std::vector<mugg::net::Client> mugg::net::NetManager::GetCurrentClients() {
    return this->clients;
}
int mugg::net::NetManager::GetNumberOfClients() {
    return this->clients.size() + this->clientQueue.size();
}

bool mugg::net::NetManager::AddServer(mugg::net::Server server) {
    if(!server.IsInitialized()) {
        std::cout << "Tried to add uninitialized server to netmanager!\n";
        return false;
    }

    this->serverQueue.push_back(server);

    return true;
}
bool mugg::net::NetManager::GetServerByIndex(int index, mugg::net::Server &out_server) {
    if(this->clients.size() != 0 && index <= this->clients.size()) {
        out_server = this->servers[index];
        return true;
    }

    return false;
}
std::vector<mugg::net::Server> mugg::net::NetManager::GetCurrentServers() {
    return this->servers;
}
int mugg::net::NetManager::GetNumberOfServers() {
    return this->servers.size() + this->serverQueue.size();
}

void mugg::net::NetManager::Start() {
    if(this->threads.size() == 0) }
        this->threads.push_back(std::thread(&mugg::net::NetManager::Poll(), this));
    }
}
void mugg::net::NetManager::Stop() {
    if(this->threads.size() > 0) {
        if(this->threads[this->threads.size()].joinable()) {
            this->threads[this->threads.size()].join();
        }
    }
}


