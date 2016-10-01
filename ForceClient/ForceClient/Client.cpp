#include "Client.h"

Client::Client()
{

}

Client::~Client()
{
	closesocket(ConnectSocket);
	WSACleanup();
}

bool Client::create_conn(std::string srv_addr, std::string srv_port)
{
	if (WSAStartup(MAKEWORD(2, 2), &wsaData))
	{
		printf("WSAStartup failed with error: %d\n");
		return false;
	}
	ZeroMemory(&hints, sizeof(hints));
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = IPPROTO_TCP;

	if (getaddrinfo(srv_addr.c_str(), srv_port.c_str(), &hints, &result))
	{
		printf("getaddrinfo failed with error\n");
		WSACleanup();
		return false;
	}

	ConnectSocket = socket(result->ai_family, result->ai_socktype,
		result->ai_protocol);

	if(ConnectSocket== INVALID_SOCKET) {
		printf("socket failed with error: %ld\n", WSAGetLastError());
		WSACleanup();
		return false;
	}

	if (connect(ConnectSocket, result->ai_addr, (int)result->ai_addrlen))
	{
		closesocket(ConnectSocket);
		ConnectSocket = INVALID_SOCKET;
		printf("invalid connection to socket\n");
		return false;
	}
}

void Client::send_data(std::string data)
{

	int send_result = send(ConnectSocket, data.c_str(), data.size(), 0);
	if (send_result == SOCKET_ERROR) {
		printf("send failed with error: %d\n", WSAGetLastError());
		closesocket(ConnectSocket);
		WSACleanup();
	}
}
void Client::close_conn()
{
	shutdown(ConnectSocket, SD_SEND);
}