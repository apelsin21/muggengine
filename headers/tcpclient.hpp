#ifndef TCPCLIENT_HPP
#define TCPCLIENT_HPP

#include <SFML/Network.hpp>
#include <iostream>

class TCPClient {
private:
	sf::TcpSocket socket;
	sf::Socket::Status status;
	
	bool connected, blocking;
	const char* address;
	unsigned short port;
	
	char* buffer;
	int maximumSize;
public:
	TCPClient(int maximumDataSize);
	~TCPClient();
	
	bool Connect(const char* address, unsigned short port);
	void Disconnect();
	
	bool SendRawData(const void* data, int size);
	bool RecieveRawData(const void* &recieved_data, int &recieved_size);
	
	void SetBlocking(bool blocking);
	bool GetIsBlocking();
	
	unsigned short GetPort();
	bool GetIsConnected();
	const char* GetAddress();
};

#endif