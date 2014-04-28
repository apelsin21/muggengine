#include "udpclient.hpp"

UDPClient::UDPClient() {
	this->is_bound = false;
	this->is_blocking = true;

	this->SetBlocking(true);
}

UDPClient::~UDPClient() {
	//TODO: Do something, deallocate stuff
}

bool UDPClient::BindToPort(unsigned short port) {
	if(this->socket.bind(port) != sf::Socket::Done) {
		std::cout << "Couldn't bind to local port: " << port << std::endl;
		this->is_bound = false;
		return false;
	}
	
    this->bound_port = port;
	this->is_bound = true;
	return true;
}

unsigned short UDPClient::GetAvailablePort() {
	return sf::Socket::AnyPort;
}

void UDPClient::SetBlocking(bool blocking) {
	this->socket.setBlocking(blocking);
	this->is_blocking = blocking;
}
bool UDPClient::GetBlocking() {
	return this->is_blocking;
}

bool UDPClient::SendMessage(std::string recipient_address, unsigned short recipient_port, std::string message) {
	if(!this->is_bound) {
		std::cout << "Tried to send data without being bound to a port!\n";
		return false;
	}

    sf::IpAddress recipient = recipient_address;

    if(this->socket.send(message.c_str(), (int)message.size(), recipient, recipient_port) != sf::Socket::Done) {
		std::cout << "Failed to send message of size " << message.size() << " to " << recipient_address << std::endl;
		return false;
	}
	
	return true;
}

const char* UDPClient::RecieveMessage(std::size_t max_len, std::string &sender_address, unsigned short &sender_port, std::size_t &out_size) {
    if(!this->is_bound) {
        std::cout << "Tried to recieve a message while not bound to a port!\n";
    }
    
    char* data = new char[max_len];

    sf::IpAddress remote_address;

    if(this->socket.receive(data, max_len, out_size, remote_address, sender_port) == sf::Socket::Done) {
        sender_address = remote_address.toString();

        return data;
    }

    return "";
}

bool UDPClient::SendPacket(sf::Packet packet, std::string recipient_address, unsigned short recipient_port) {
    if(!this->is_bound) {
        std::cout << "Tried to send packet without being bound to socket!\n";
        return false;
    }

    sf::IpAddress address = recipient_address;

    if(this->socket.send(packet, address, recipient_port) == sf::Socket::Done) {
        return true;
    }

    return false;
}
sf::Packet UDPClient::RecievePacket(std::string &sender_address, unsigned short &sender_port) {
    if(!this->is_bound) {
        std::cout << "Tried to listen for packet while not bound to port!\n";
    }

    sf::IpAddress address;
    sf::Packet packet;

    if(this->socket.receive(packet, address, sender_port) == sf::Socket::Done) {
        sender_address = address.toString();
        return packet;
    }
}
