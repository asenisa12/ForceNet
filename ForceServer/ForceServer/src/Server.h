#pragma once

#define WIN32_LEAN_AND_MEAN

#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdlib.h>
#include <stdio.h>
#include <thread>
#include <mutex>
#include <string>
#include <vector>
#include <algorithm>
#include <map>

#pragma comment (lib, "Ws2_32.lib")


class Server
{
	int cli_num;
	static const int MAX_CLIENTS = 5;
	static const int BUFF_SIZE = 1024;
	std::map<SOCKET, std::string> coord;
	WSADATA wsaData;
	SOCKET ListenSocket;
	std::mutex client_mutex;
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