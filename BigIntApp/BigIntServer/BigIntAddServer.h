#pragma once
#include "IdempotentUDPServer.h"

class BigIntAddServer :
	public IdempotentUDPServer
{
private:
	virtual std::vector<char> OnRequest(const std::vector<char> &request, const UDPSocket::SocketAddr &raddr);
public:
	BigIntAddServer(void);
	~BigIntAddServer(void);
};
