#include "StdAfx.h"
#include "IdempotentUDPServer.h"

IdempotentUDPServer::IdempotentUDPServer(void)
{
}

IdempotentUDPServer::~IdempotentUDPServer(void)
{
}

void IdempotentUDPServer::InitServer(const UDPSocket::SocketAddr &addr)
{
	socket.Bind(addr);
}

void IdempotentUDPServer::ServerLoop()
{
	while (1) {
		std::vector<char> request;
		UDPSocket::SocketAddr raddr;
		if (!socket.RecvFrom(request, raddr, -1)) {
			Log(_T("��������ʱ����"));
			continue;
		}

		if (request.size() < sizeof(int)) {
			Log(_T("��Ч����"));
			continue;
		}
		int seq;
		memcpy(&seq, &request[0], sizeof(int));
		request.erase(request.begin(), request.begin() + 4);

		Log(_T("�յ����� %hs ������, ˳��� %d : %.*hs"), raddr.toString().c_str(), seq, request.size(), request.size() ? &request[0] : "");

		std::vector<char> response;
		
		response = OnRequest(request, raddr);
		
		Log(_T("���ͻ�Ӧ, ˳��� %d : %.*hs"), seq, response.size(), response.size() ? &response[0] : "");
		
		response.insert(response.begin(), sizeof(int), '\0');
		memcpy(&response[0], &seq, sizeof(int));

		if (!socket.SendTo(response, raddr)) {
			Log(_T("���ͻ�Ӧʱ����"));
			continue;
		}
	}
}