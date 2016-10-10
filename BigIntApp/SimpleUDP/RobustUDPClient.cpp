#include "StdAfx.h"
#include "RobustUDPClient.h"

RobustUDPClient::RobustUDPClient(void)
{
	seq = 0;
}

RobustUDPClient::~RobustUDPClient(void)
{
}

void RobustUDPClient::SendRequest(const std::vector<char> &request)
{
	seq++;

	Log(_T("��������: ˳��� %d, %.*hs"), seq, request.size(), request.size() ? &request[0] : "");

	std::vector<char> buf = request;
	buf.insert(buf.begin(), sizeof(int), '\0');
	memcpy(&buf[0], &seq, sizeof(int));

	if (!socket.SendTo(buf, srvaddr)) {
		Log(_T("��������ʱ����"));
	}
}
bool RobustUDPClient::WaitResponse(int timeout)
{
	while (1) {
		bool ret = socket.RecvFrom(response, raddr, timeout);
		if (!ret) {
			Log(_T("���ջ�Ӧʱ��ʱ�����"));
			return false;
		}
		
		if (response.size() < sizeof(int)) {
			Log(_T("��Ч����"));
			return false;
		}

		int rseq;
		memcpy(&rseq, &response[0], sizeof(int));
		if (rseq != seq) {
			Log(_T("˳��Ų�ƥ��, rseq = %d, seq = %d"), rseq, seq);
		} else {
			response.erase(response.begin(), response.begin() + sizeof(int));
			return true;
		}
	}
}

void RobustUDPClient::SetServer(const UDPSocket::SocketAddr &addr)
{
	srvaddr = addr;
}

std::vector<char> RobustUDPClient::DoRequest(const std::vector<char> &request)
{
	while (1) {
		SendRequest(request);
		if (WaitResponse(CLIENT_TIMEOUT)) {
			break;
		}
		Log(_T("�ȴ���ʱ, �����ط�"));
	}
	Log(_T("�յ���Ӧ: %.*hs"), response.size(), response.size() ? &response[0] : "");
	return response;
}