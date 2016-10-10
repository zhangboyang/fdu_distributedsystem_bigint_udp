// SimpleUDP.cpp : 定义 DLL 应用程序的导出函数。
//

#include "stdafx.h"
#include <stdarg.h>

#include <vector>

double send_failrate = 0;
double send_waitrate = 0;

MsgLogger *pLogger = NULL;

static std::vector<LPTSTR> log_buffer;
void Log(LPCTSTR fmt, ...)
{
	va_list ap;
	va_start(ap, fmt);
	TCHAR buf[MAXLINE];
	_vsntprintf(buf, MAXLINE, fmt, ap);
	if (pLogger) {
		// output buffer first
		for (std::vector<LPTSTR>::iterator it = log_buffer.begin(); it != log_buffer.end(); it++) {
			pLogger->Log(*it);
			free(*it);
		}
		log_buffer.clear();
		
		// log current msg
		pLogger->Log(buf);
	} else {
		// log to buffer
		log_buffer.push_back(_tcsdup(buf));
	}
	va_end(ap);
}

bool RandomBool(double truerate)
{
	double r = (double) rand() / RAND_MAX;
	return r < truerate;
}

static char *wcs2cs(const wchar_t *wstr) // note: convert to wchar_t to UTF-8
{
    size_t len = WideCharToMultiByte(CP_UTF8, 0, wstr, -1, NULL, 0, NULL, NULL);
    if (len == 0) exit(1);
    char *ret = new char[len];
    WideCharToMultiByte(CP_UTF8, 0, wstr, -1, ret, len, NULL, NULL);
    return ret;
}
static wchar_t *cs2wcs(const char *str) // cstring to wide-cstring, alloc memory
{
    size_t len = MultiByteToWideChar(CP_UTF8, 0, str, -1, NULL, 0);
    if (len == 0) exit(1);
    wchar_t *ret = new wchar_t[len]; // dislike mbstowcs(), no +1 here
    MultiByteToWideChar(CP_UTF8, 0, str, -1, ret, len);
    return ret;
}

std::wstring s2ws(const std::string &str) // convert string to wstring
{
    const char *src = str.c_str();
    wchar_t *dest = cs2wcs(src);
    std::wstring ret(dest);
    delete[] dest;
    return ret;
}

std::string ws2s(const std::wstring &wstr) // convert wstring to string
{
    const wchar_t *src = wstr.c_str();
    char *dest = wcs2cs(src);
    std::string ret(dest);
    delete[] dest;
    return ret;
}