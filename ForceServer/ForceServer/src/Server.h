#pragma once

//#undef UNICODE

#define WIN32_LEAN_AND_MEAN


#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdlib.h>
#include <stdio.h>
#include <thread>
#include <string>
#include <vector>
#include <algorithm>

// Need to link with Ws2_32.lib
#pragma comment (lib, "Ws2_32.lib")
// #pragma comment (lib, "Mswsock.lib")


class Server
{
	static const int MAX_CLIENTS = 5;
	WSADATA wsaData;
	SOCKET ListenSocket;
	//SOCKET ClientSocket;
	std::vector<SOCKET> clients;
	struct addrinfo hints;
	struct addrinfo *result;
	std::string addr_;
	std::string port_;
public:
	Server(std::string addr, std::string port);
	void client_work(SOCKET cliSock);
	bool init();
	~Server();

	void run();

};