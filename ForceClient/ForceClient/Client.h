#pragma once

#define WIN32_LEAN_AND_MEAN


#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdlib.h>
#include <stdio.h>
#include <string>

// Need to link with Ws2_32.lib
#pragma comment (lib, "Ws2_32.lib")
// #pragma comment (lib, "Mswsock.lib")


class Client
{
	static const int SIZE = 1024;
	WSADATA wsaData;
	SOCKET ConnectSocket = INVALID_SOCKET;
	struct addrinfo *result = NULL,
		hints;

public:
	Client();
	bool create_conn(std::string srv_addr, std::string srv_port);
	void send_data(std::string);
	std::string recv_data();
	void close_conn();
	~Client();

};