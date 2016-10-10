#include "StdAfx.h"
#include "BigIntAddServer.h"
#include "BigInt.h"

BigIntAddServer::BigIntAddServer(void)
{
}

BigIntAddServer::~BigIntAddServer(void)
{
}

std::vector<char> BigIntAddServer::OnRequest(const std::vector<char> &request, const UDPSocket::SocketAddr &raddr)
{
	std::vector<char> ret;
	std::vector<char>::const_iterator p, it;
	std::string a, b, c;

	p = std::find(request.begin(), request.end(), '+');
	if (p == request.end()) goto fail;
	
	for (it = request.begin(); it != p; it++) {
		a += *it;
	}
	for (it++; it != request.end(); it++) {
		b += *it;
	}
	
	Log(_T("a=%hs b=%hs"), a.c_str(), b.c_str());
	if (!isnum(a) || !isnum(b)) goto fail;
	c = add(a, b);
	Log(_T("c=%hs"), c.c_str());

	ret = std::vector<char>(c.c_str(), c.c_str() + c.length());
	return ret;
fail:
	const char *errmsg = "ERROR";
	ret = std::vector<char>(errmsg, errmsg + strlen(errmsg));
	return ret;
}