#include "client.hpp"

mugg::net::Client::Client() {
    this->maxConnections = 1;
    this->maxChannels = 2;
    this->incThrottle = 0;
    this->outThrottle = 0;
    this->address.port = 2300;

    this->initialized = false;
    this->connected = false;
}
mugg::net::Client::~Client() {
    if(this->connected)
        this->Disconnect(0);

    if(this->initialized)
        enet_host_destroy(this->host);
}

bool mugg::net::Client::Initialize(int maxChannels = 2, int incThrottle = 0, int outThrottle = 0) {
    this->host = enet_host_create(NULL, 1, maxChannels, incThrottle, outThrottle);

    if(this->host == NULL) {
        std::cout << "Error occurred initializing an ENet client!\n";
        this->initialized = false;
        return false;
    }

    this->initialized = true;
    return true;
}

bool mugg::net::Client::Connect(const char* address, unsigned short port, int timeout = 5000) {
    if(!this->initialized) {
        std::cout << "Tried to connect an uninitialized client!\n";
        this->connected = false;
        return false;
    }
    
    if(address == "") {
        std::cout << "Can't connect to empty address!\n";
        this->connected = false;
        return false;
    }
    if(port == 0) {
        std::cout << "Can't connect to address with empty port!\n";
        this->connected = false;
        return false;
    }
    
    enet_address_set_host(&this->address, address);
    this->address.port = port;

    this->peer = enet_host_connect(this->host, &this->address, this->maxChannels, 0);

    if(this->peer == NULL) {
        std::cout << "No available peers to connect to " << address << ":" << port << "!\n";
        this->connected = false;
        return false;
    }

    if(enet_host_service(this->host, &this->event, timeout) > 0 && this->event.type == ENET_EVENT_TYPE_CONNECT) {
        this->connected = true;
        return true;
    }

    enet_peer_reset(this->peer);

    this->connected = false;
    return false;
}
void mugg::net::Client::Disconnect(int timeout = 3000) {
    if(!this->initialized) {
        std::cout << "Tried to disconnect an uninitialized client!\n";
        return;
    }
    else if(!this->connected) {
        std::cout << "Tried to disconnect an unconnected client!\n";
        return;
    }

    enet_peer_disconnect(this->peer, 0);

    while(enet_host_service(this->host, &this->event, timeout) > 0) {
        switch(this->event.type) {
            case ENET_EVENT_TYPE_RECEIVE:
                enet_packet_destroy(this->event.packet);
                break;
            case ENET_EVENT_TYPE_DISCONNECT:
                this->connected = false;
                return;
        }
    }

    //Disconnect forcefully, since it hasn't got a disconnect event
    enet_peer_reset(this->peer);
}

bool mugg::net::Client::IsConnected() {
    return this->connected;
}

void mugg::net::Client::PollEvents(int timeout = 0) {
    if(!this->initialized) {
        std::cout << "Tried to poll an unintialized client!\n";
        return;
    } 
    
    while(enet_host_service(this->host, &this->event, timeout) > 0) {
        switch(this->event.type) {
            case ENET_EVENT_TYPE_CONNECT:
                std::cout << "CLIENT: CONNECT EVENT\n";
                break;
            case ENET_EVENT_TYPE_RECEIVE:
                std::cout << "CLIENT: RECEIVE EVENT\n";
                break;
            case ENET_EVENT_TYPE_DISCONNECT:
                std::cout << "CLIENT: DISCONNECT EVENT\n";
                break;
        }
    }
}
