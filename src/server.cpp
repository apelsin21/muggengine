#include "server.hpp"

mugg::net::Server::Server(mugg::net::NetManager* parent) : NetBase(parent) {
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

std::string mugg::net::Server::GetClientAddressByIndex(unsigned int index) {
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

unsigned int mugg::net::Server::GetNumberOfClients() {
    return this->numberOfClients;
}

void mugg::net::Server::Poll() {
    if(!this->initialized) {
        std::cout << "Tried to poll non-initialized server!\n";
        return;
    }
    
    this->latestEvent = mugg::net::Event::None;

    while(enet_host_service(this->host, &this->event, 0) > 0) {
        switch(event.type) {
            case ENET_EVENT_TYPE_CONNECT:
                this->numberOfClients++;

                this->latestEvent = mugg::net::Event::Connected;
                this->latestEventAddress = this->AddressToString(this->event.peer->address);
            
            case ENET_EVENT_TYPE_NONE:
                this->latestEvent = mugg::net::Event::None;
                break;
            case ENET_EVENT_TYPE_RECEIVE:
                this->latestEvent = mugg::net::Event::Received;
                this->latestEventAddress = this->AddressToString(this->event.peer->address);
                this->latestEventData = this->event.packet->data;

                break;
            case ENET_EVENT_TYPE_DISCONNECT:
                this->numberOfClients--;

                this->latestEvent = mugg::net::Event::Disconnected;
                this->latestEventAddress = this->AddressToString(this->event.peer->address);

                break;
        }
    }
}
