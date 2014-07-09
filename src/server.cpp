#include "server.hpp"

mugg::net::Server::Server() {
    this->maxConnections = 5;
    this->maxChannels = 2;
    this->incThrottle = 0;
    this->outThrottle = 0;
    this->numberOfClients = 0;

    this->address.host = ENET_HOST_ANY;
    this->address.port = 2300;
    
    this->initialized = false;
}
mugg::net::Server::~Server() {
    if(this->initialized)
        enet_host_destroy(this->host);
}

bool mugg::net::Server::Initialize(const char* address, unsigned short port, int maxConnections, int maxChannels, int incThrottle, int outThrottle) {
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

    this->host = enet_host_create(&this->address, maxConnections, maxChannels, incThrottle, outThrottle);

    if(this->host == NULL) {
        std::cout << "Failed to create ENet host!\n";
        this->initialized = false;
        return false;
    }

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

    this->host = enet_host_create(&this->address, this->maxConnections, this->maxChannels, this->incThrottle, this->outThrottle);

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
                    
                    while(enet_host_service(this->host, &this->event, 3000) > 0) {
                        switch(this->event.type) {
                            case ENET_EVENT_TYPE_RECEIVE:
                                enet_packet_destroy(this->event.packet);
                                break;
                            case ENET_EVENT_TYPE_DISCONNECT:
                                break;
                        }
                    }

                } else {
                    std::cout << this->AddressToString(this->event.peer->address) << " has connected.\n";
                    this->connectedClients.push_back(this->event.peer->address);
                    this->latestEvent = mugg::net::Event::Connected;
                    
                    this->numberOfClients++;
                }    
                break;
            case ENET_EVENT_TYPE_NONE:
                this->latestEvent = mugg::net::Event::None;
                break;
            case ENET_EVENT_TYPE_RECEIVE:
                std::cout << "Recieved packet from "
                            << event.peer->data
                            << " containing: "
                            << event.packet->data
                            << ", size: "
                            << event.packet->dataLength
                            << " on channel: "
                            << event.channelID
                            << std::endl;
                this->latestEvent = mugg::net::Event::Received;

                break;
            case ENET_EVENT_TYPE_DISCONNECT:
                std::cout << this->AddressToString(this->event.peer->address) << " has disconnected!\n";

                if(this->numberOfClients != 0) {
                    this->numberOfClients--;
                }

                this->latestEvent = mugg::net::Event::Disconnected;

                break;
        }
    }
}
