#include <iostream>

#include "Server.h"

// Need to link with Ws2_32.lib
//#pragma comment (lib, "Ws2_32.lib")
//#pragma comment (lib, "Mswsock.lib")

int __cdecl main()
{
	Server srv("","5667");
	srv.init();
	srv.run();
	return 0;
}