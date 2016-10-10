#pragma once

#include "SimpleUDP_common.h"
#include "UDPSocket.h"

class SIMPLEUDP_API IdempotentUDPServer
{
private:
	UDPSocket socket;
	virtual std::vector<char> OnRequest(const std::vector<char> &request, const UDPSocket::SocketAddr &raddr) = 0;
public:
	IdempotentUDPServer(void);
	~IdempotentUDPServer(void);
	void InitServer(const UDPSocket::SocketAddr &addr);
	void ServerLoop();
};
