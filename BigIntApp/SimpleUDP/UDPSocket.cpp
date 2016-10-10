#include "StdAfx.h"
#include "UDPSocket.h"

UDPSocket::SocketAddr::SocketAddr()
{
	addr.sin_family = AF_INET;
	addr.sin_port = DEFAULTPORT;
	addr.sin_addr.S_un.S_addr = INADDR_ANY;
}

UDPSocket::SocketAddr::SocketAddr(short port)
{
	addr.sin_family = AF_INET;
	addr.sin_port = htons(port);
	addr.sin_addr.S_un.S_addr = INADDR_ANY;
}

UDPSocket::SocketAddr::SocketAddr(const std::string &addrstr)
{
	char host[1024];
	int port;
	sscanf(addrstr.c_str(), "%1024[^:]:%d", host, &port);
	addr.sin_family = AF_INET;
	addr.sin_port = htons(port);
	addr.sin_addr.S_un.S_addr = inet_addr(host);
}

std::string UDPSocket::SocketAddr::toString() const
{
	char portstr[10];
	sprintf(portstr, "%u", (unsigned) ntohs(addr.sin_port));
	return std::string(inet_ntoa(addr.sin_addr)) + ":" + portstr;
}

UDPSocket::UDPSocket(void)
{
	init_flag = false;
}

UDPSocket::~UDPSocket(void)
{
	if (init_flag) { Cleanup(); }
}

void UDPSocket::Init()
{
	if (init_flag) return;
	s = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	if (s != SOCKET_ERROR) {
		init_flag = true;
	} else {
		Log(_T("无法创建套接字"));
	}
}

void UDPSocket::Cleanup()
{
	closesocket(s);
	init_flag = false;
}

bool UDPSocket::Bind(const UDPSocket::SocketAddr &addr)
{
	Init();
	if (bind(s, (const sockaddr *) &addr.addr, sizeof(addr.addr)) == SOCKET_ERROR) {
		Log(_T("bind 错误 %d"), WSAGetLastError());
		return false;
	}
	return true;
}
bool UDPSocket::SendTo(const std::vector<char> &data, const UDPSocket::SocketAddr &addr)
{
	Init();
	if (data.size() == 0) {
		Log(_T("没有要发送的数据"));
		return false;
	}
	if (RandomBool(send_failrate)) {
		Log(_T("假装发送成功, 实际并未发送"));
		return true;
	}
	if (RandomBool(send_waitrate)) {
		Log(_T("发送前故意延迟 3 秒"));
		Sleep(3000);
	}
	if (sendto(s, &data[0], data.size(), 0, (const sockaddr *) &addr.addr, sizeof(addr.addr)) == SOCKET_ERROR) {
		Log(_T("sendto 错误 %d"), WSAGetLastError());
		return false;
	}
	return true;
}
bool UDPSocket::RecvFrom(std::vector<char> &rdata, UDPSocket::SocketAddr &raddr, int timeout)
{
	Init();
	char buf[RECVBUF];

	if (timeout >= 0) {
		struct timeval tv;
		tv.tv_sec = timeout / 1000;
		tv.tv_usec = timeout % 1000 * 1000;
		fd_set fdset;
		FD_ZERO(&fdset);
		FD_SET(s, &fdset);
		int ret = select(0, &fdset, NULL, NULL, &tv);
		if (ret == SOCKET_ERROR) {
			Log(_T("select 错误 %d"), WSAGetLastError());
			return false;
		}
		if (ret == 0) {
			Log(_T("RecvFrom 超时"));
			return false;
		}
	}

	int slen = sizeof(raddr.addr);
	int len = recvfrom(s, buf, sizeof(buf), 0, (sockaddr *) &raddr.addr, &slen);
	if (len == SOCKET_ERROR) {
		Log(_T("recvfrom 错误 %d"), WSAGetLastError());
		return false;
	}
	rdata = std::vector<char>(buf, buf + len);
	return true;
}

static WSADATA wsa;
void UDPSocket::InitWSA()
{
	WSAStartup(MAKEWORD(2, 2), &wsa);
}
void UDPSocket::CleanupWSA()
{
	WSACleanup();
}

