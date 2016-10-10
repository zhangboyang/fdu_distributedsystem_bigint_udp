#pragma once

#include "SimpleUDP_common.h"
#include "UDPSocket.h"

#define CLIENT_TIMEOUT 1000
class SIMPLEUDP_API RobustUDPClient
{
private:
	UDPSocket::SocketAddr srvaddr, raddr;
	UDPSocket socket;
	int seq;
	std::vector<char> response;
	void SendRequest(const std::vector<char> &request);
	bool WaitResponse(int timeout);
public:
	RobustUDPClient(void);
	~RobustUDPClient(void);
	void SetServer(const UDPSocket::SocketAddr &addr);
	std::vector<char> DoRequest(const std::vector<char> &request);
};
