#include "Client.h"

int main()
{
	Client connection;
	connection.create_conn("127.0.0.1", "5667");

	connection.send_data("ludnicaaa");
	std::string data = connection.recv_data();
	printf("%s\n",data.c_str());
	system("pause");
	//connection.close_conn();
	
	return 0;
}