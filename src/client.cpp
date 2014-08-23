#include "client.hpp"

mugg::net::Client::Client() {
    this->maxConnections = 1;
    this->maxChannels = 2;
    this->inLimit = 0;
    this->outLimit = 0;
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

bool mugg::net::Client::Initialize(int maxChannels = 2, unsigned int inLimit = 0, unsigned int outLimit = 0) {
    this->host = enet_host_create(NULL, 1, maxChannels, inLimit, outLimit);

    if(this->host == NULL) {
        std::cout << "Error occurred initializing an ENet client!\n";
        this->initialized = false;
        return false;
    }

    this->initialized = true;
    return true;
}
bool mugg::net::Client::Initialize() {
    this->host = enet_host_create(NULL, 1, this->maxChannels, this->inLimit, this->outLimit);

    if(this->host == NULL) {
        std::cout << "Error occurred initializing a net client!\n";
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
        std::cout << "No peer available to connect to " << address << ":" << port << "!\n";
        std::cout << "This is probably because you already are connected!\n";
        this->connected = false;
        return false;
    }

    if(enet_host_service(this->host, &this->event, timeout) > 0 && this->event.type == ENET_EVENT_TYPE_CONNECT) {
        this->connected = true;
        return true;
    }

    //Connecting failed, forcefully reset.
    enet_peer_reset(this->peer);

    this->connected = false;
    return false;
}
//If it doesn't get a disconnect event within the timeout, it forcefully resets the connection, which sends no disconnect
//event to the other end
void mugg::net::Client::Disconnect(int timeout = 3000) {
    if(!this->initialized) {
        std::cout << "Tried to disconnect an uninitialized client!\n";
        return;
    }
    else if(!this->connected) {
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

    enet_peer_reset(this->peer);
}

bool mugg::net::Client::IsConnected() {
    return this->connected;
}

bool mugg::net::Client::SendPacket(mugg::net::StringPacket packet, unsigned int channel) {
    if(!this->initialized) {
        std::cout << "Client tried to send a packet, but isn't initialized!\n";
        return false;
    }
    if(!this->connected) {
        std::cout << "Client tried to send a packet, but it isn't connected!\n";
        return false;
    }
    
    enet_peer_send(this->peer, channel, packet.GetInternalPacket());

    return true;
}

void mugg::net::Client::PollEvents(int timeout = 0) {
    if(!this->initialized) {
        std::cout << "Tried to poll an unintialized client!\n";
        return;
    } 
    
    while(enet_host_service(this->host, &this->event, timeout) > 0) {
        switch(this->event.type) {
            case ENET_EVENT_TYPE_CONNECT:
                this->latestEvent = mugg::net::Event::Connected;
                this->peer = event.peer;
                this->connected = true;
                break;
            case ENET_EVENT_TYPE_RECEIVE:
                this->latestEvent = mugg::net::Event::Received;
                this->latestEventData = (unsigned char*)this->event.peer->data;
                break;
            case ENET_EVENT_TYPE_DISCONNECT:
                this->latestEvent = mugg::net::Event::Disconnected;
                this->connected = false;
                break;
        }
    }
}
