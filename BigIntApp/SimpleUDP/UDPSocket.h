#pragma once

#include "SimpleUDP_common.h"

#include <vector>
#include <string>

#define RECVBUF 4096
#define DEFAULTPORT 1234

class SIMPLEUDP_API UDPSocket
{
private:
	SOCKET s;
	bool init_flag;
public:
	class SIMPLEUDP_API SocketAddr {
	public:
		struct sockaddr_in addr;
		SocketAddr();
		SocketAddr(short port);
		SocketAddr(const std::string &addrstr);
		std::string toString() const;
	};
	UDPSocket(void);
	~UDPSocket(void);

	void Init();
	void Cleanup();

	bool Bind(const UDPSocket::SocketAddr &addr);
	bool SendTo(const std::vector<char> &data, const UDPSocket::SocketAddr &addr);
	bool RecvFrom(std::vector<char> &rdata, UDPSocket::SocketAddr &raddr, int timeout);
	static void InitWSA();
	static void CleanupWSA();
};
