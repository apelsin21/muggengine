#include "tcpclient.hpp"

TCPClient::TCPClient(int maximumDataSize) {
	this->buffer = new char[maximumDataSize];
	this->maximumSize = maximumDataSize;
	
	this->blocking = true;
	this->SetBlocking(this->blocking);
}

TCPClient::~TCPClient() {
	delete this->buffer;
}

bool TCPClient::Connect(const char* address, unsigned short port) {
	this->status = this->socket.connect(address, port);
	
	if(status == sf::Socket::Done) {
		this->address = address;
		this->port = port;
		this->connected = true;
		return true;
	} else {
		return false;
	}
}

void TCPClient::Disconnect() {
	this->socket.disconnect();
}

bool TCPClient::SendRawData(const void* data, int size) {
	if(!this->connected) {
		std::cout << "Error: Tried to send data while unconnected.\n";
		return false;
	} 
	this->status = this->socket.send(data, size);

	if(this->status == sf::Socket::Done) {
		std::cout << "Successfully sent data\n";
		return true;
	} else {
		std::cout << "Failed to send data\n";
		return false;
	}
}

bool TCPClient::RecieveRawData(const void* &recieved_data, int &recieved_size) {
	if(!this->connected) {
		std::cout << "Error: Tried to recieve data while unconnected.\n";
		return false;
	}
	
	this->status = this->socket.receive(this->buffer, (std::size_t)this->maximumSize, (std::size_t&)recieved_size);
	
	if(this->status == sf::Socket::Done) {
		std::cout << "Successfully recieved data.\n";
		return true;
	} else {
		std::cout << "Failed to recieve data.\n";
		return false;
	}
}

void TCPClient::SetBlocking(bool blocking) {
	this->blocking = blocking;
	
	this->socket.setBlocking(blocking);
}

bool TCPClient::GetIsBlocking() {
	return this->blocking;
}

unsigned short TCPClient::GetPort() {
	return this->port;
}

const char* TCPClient::GetAddress() {
	return this->address;
}

bool TCPClient::GetIsConnected() {
	return this->connected;
}
