#include "server.hpp"

mugg::net::Server::Server() {
    this->maxConnections = 5;
    this->maxChannels = 2;
    this->inLimit = 0;
    this->outLimit = 0;
    this->numberOfClients = 0;

    this->address.host = ENET_HOST_ANY;
    this->address.port = 2300;
    
    this->initialized = false;

    this->latestEvent = mugg::net::Event::None;
}
mugg::net::Server::~Server() {
    if(this->initialized)
        enet_host_destroy(this->host);
}

bool mugg::net::Server::Initialize(const char* address, unsigned short port, int maxConnections, int maxChannels, unsigned int inLimit, unsigned int outLimit) {
    if(address == "") {
        std::cout << "Tried to bind server to empty address!\n";
        this->initialized = false;
        return false;
    }

    if(port == 0) {
        std::cout << "Tried to bind server to port 0!\n";
        this->initialized = false;
        return false;
    }

    enet_address_set_host(&this->address, address);
    this->address.port = port;

    this->host = enet_host_create(&this->address, maxConnections, maxChannels, inLimit, outLimit);

    if(this->host == NULL) {
        std::cout << "Failed to create ENet host!\n";
        this->initialized = false;
        return false;
    }

    this->inLimit = inLimit;
    this->outLimit = outLimit;
    this->maxConnections = maxConnections;
    this->maxChannels = maxChannels;

    this->initialized = true;
    return true;
}

bool mugg::net::Server::Initialize(unsigned short port) {
    if(port == 0) {
        std::cout << "Server port can't be 0!\n";
        this->initialized = false;
        return false;
    }

    this->address.port = port;

    this->host = enet_host_create(&this->address, this->maxConnections, this->maxChannels, this->inLimit, this->outLimit);

    if(this->host == NULL) {
        std::cout << "Failed to create ENet host!\n";
        this->initialized = false;
        return false;
    }

    this->initialized = true;
    return true;
}

const char* mugg::net::Server::AddressToString(ENetAddress address) {
    unsigned char bytes[4];
    bytes[0] = address.host & 0xFF;
    bytes[1] = (address.host >> 8) & 0xFF;
    bytes[2] = (address.host >> 16) & 0xFF;
    bytes[3] = (address.host >> 24) & 0xFF;   

    char buffer[100];

    snprintf(buffer, 100, "%d.%d.%d.%d:%d", bytes[0], bytes[1], bytes[2], bytes[3], address.port);

    return std::string(buffer).c_str();
}

const char* mugg::net::Server::GetClientAddressByIndex(unsigned int index) {
    if(!this->initialized) {
        std::cout << "Tried to get client address of uninitialized server!\n";
        return "";
    }

    if(this->connectedClients.size() <= 0) {
        std::cout << "Tried to get client address of server with no clients!\n";
        return "";
    }

    if(index > this->connectedClients.size()) {
        std::cout << "Tried to get out of bounds address from server!\n";
        return "";
    } else {
        return this->AddressToString(this->connectedClients[index]);        
    }
}

int mugg::net::Server::GetNumberOfClients() {
    return this->numberOfClients;
}

void mugg::net::Server::SetBandwidthLimit(unsigned int incThrottle, unsigned int outThrottle) {
    enet_host_bandwidth_limit(this->host, incThrottle, outThrottle);
}

void mugg::net::Server::PollEvents(int timeout = 0) {
    if(!this->initialized) {
        std::cout << "Tried to poll non-initialized server!\n";
        return;
    }
    
    while(enet_host_service(this->host, &this->event, timeout) > 0) {
        switch(event.type) {
            case ENET_EVENT_TYPE_CONNECT:
                if(this->numberOfClients == this->maxConnections) {
                    std::cout << "A client tried to connect, but max connections of the server has been reached. Disconnecting client!\n";
                    enet_peer_disconnect(event.peer, 0);
                } else {
                    this->latestEvent = mugg::net::Event::Connected;
                    this->connectedClients.push_back(this->event.peer->address);
                    this->numberOfClients++;
                    std::cout << this->AddressToString(this->event.peer->address) << " connected!\n";
                }    
                break;
            case ENET_EVENT_TYPE_NONE:
                this->latestEvent = mugg::net::Event::None;
                break;
            case ENET_EVENT_TYPE_RECEIVE:
                std::cout << this->AddressToString(event.peer->address)
                            << ": "
                            << this->event.packet->data
                            << std::endl;
                this->latestEvent = mugg::net::Event::Received;

                break;
            case ENET_EVENT_TYPE_DISCONNECT:
                if(this->numberOfClients != 0) {
                    this->numberOfClients--;
                }

                std::cout << this->AddressToString(this->event.peer->address) << " disconnected!\n";

                this->latestEvent = mugg::net::Event::Disconnected;

                break;
        }
    }
}
