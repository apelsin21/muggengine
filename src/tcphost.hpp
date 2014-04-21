#ifndef TCPHOST_HPP
#define TCPHOST_HPP

#include <SFML/Network.hpp>

class TCPHost {
private:
	sf::TcpListener listenerSocket;
	sf::Socket::Status status;
	
	int port;
public:
	TCPHost();
	~TCPHost();
	
	unsigned short GetLocalPort();
	
	bool Listen(unsigned short port);
};

#endif