// BigIntServer.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <ctime>
#include "SimpleUDP.h"


int _tmain(int argc, _TCHAR* argv[])
{
	// for _putts
	setlocale(LC_ALL, "chs");
	
	// set fail rate
	srand(time(NULL));
	send_failrate = 0.1;
	send_waitrate = 0.1;

	// init WSA
	UDPSocket::InitWSA();
	
	// set logger
	ConsoleLogger logger;
	pLogger = &logger;

	// init and run the server
	BigIntAddServer srv;
	srv.InitServer(UDPSocket::SocketAddr(1234));
	srv.ServerLoop();

	// cleanup WSA
	UDPSocket::CleanupWSA();

	return 0;
}

