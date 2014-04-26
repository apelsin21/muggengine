#ifndef UDPCLIENT_HPP
#define UDPCLIENT_HPP

#include <iostream>
#include <vector>
#include <string>

#include <SFML/Network.hpp>

class UDPClient {
private:
	sf::UdpSocket socket;
	sf::IpAddress server_address;
	unsigned short bound_port;
	bool is_blocking;
	bool is_bound;
public:
	UDPClient();
	~UDPClient();

	bool BindToPort(unsigned short port);

	unsigned short GetAvailablePort();

	void SetBlocking(bool blocking);
	bool GetBlocking();

	bool SendMessage(std::string recipient_address, unsigned short recipient_port, std::string message);
	const char* RecieveMessage(std::string &recipient_address, unsigned short &recipient_port, std::size_t &out_size);

	void SetServerPort(unsigned short port);
	unsigned short GetServerPort();
};

#endif
