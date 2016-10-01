#include "Client.h"

int main()
{
	Client connection;
	connection.create_conn("127.0.0.1", "5667");
	connection.send_data("ludnicaaa");
	//connection.close_conn();
	
	return 0;
}