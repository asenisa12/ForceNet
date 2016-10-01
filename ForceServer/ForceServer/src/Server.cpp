#include "Server.h"


Server::Server(std::string addr, std::string port)
	:addr_(addr), port_(port)
{
	ListenSocket = INVALID_SOCKET;
//	ClientSocket = INVALID_SOCKET;
	result = NULL;

	ZeroMemory(&hints, sizeof(hints));
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = IPPROTO_TCP;
	hints.ai_flags = AI_PASSIVE;

	

}

bool Server::init()
{
	int resul;


	resul = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (resul != 0) {
		printf("WSAStartup Error\n");
		return false;
	}
	
	resul = getaddrinfo(NULL, port_.c_str(), &hints, &result);
	if (resul != 0) {
		printf("getaddrinfo failed with error: %d\n", resul);
		WSACleanup();
		return false;
	}

	ListenSocket = socket(result->ai_family,
		result->ai_socktype, result->ai_protocol);

	if (ListenSocket == INVALID_SOCKET)
	{
		printf("socket failed with error: %ld\n", WSAGetLastError());
		freeaddrinfo(result);
		WSACleanup();
		return false;
	}


	if (bind(ListenSocket, result->ai_addr, (int)result->ai_addrlen) == SOCKET_ERROR)
	{
		printf("bind failed with error: %d\n", WSAGetLastError());
		freeaddrinfo(result);
		closesocket(ListenSocket);
		WSACleanup();
		return false;
	}
	resul = listen(ListenSocket, SOMAXCONN);
	if (resul == SOCKET_ERROR)
	{
		printf("listen failed with error: %d\n", WSAGetLastError());
		closesocket(ListenSocket);
		WSACleanup();
		return false;
	}

	
}

void Server::client_work(SOCKET cliSock)
{
	char buff[1024];
	memset(buff, 0, 1024);
	int size = 1024;
	do {

		size = recv(cliSock, buff, 1024, 0);
		buff[size] = '\0';
		//send(cliSock, buff, 1024, 0);
		printf("%s\n", buff);
	} while (size > 0);

	closesocket(cliSock);
	clients.erase(std::remove(clients.begin(), clients.end(), cliSock), clients.end());
}

void Server::run()
{
	int cli_num = 0;
	while (cli_num < MAX_CLIENTS)
	{

		SOCKET cli = accept(ListenSocket, NULL, NULL);
		if (cli == INVALID_SOCKET) {
			printf("accept failed with error: %d\n", WSAGetLastError());
			closesocket(ListenSocket);
			WSACleanup();
			continue;
		}
		cli_num++;
		std::thread client_thread(&Server::client_work,this, cli);
		client_thread.detach();
		clients.push_back(cli);
	}
}

Server::~Server()
{
		
	closesocket(ListenSocket);
	for (auto cli : clients)
		closesocket(cli);

	//closesocket(ClientSocket);
	WSACleanup();
}