#include <iostream>

#include "Server.h"

int __cdecl main()
{
	Server srv("","5667");
	srv.init();
	srv.run();
	return 0;
}