#pragma once

#include "SimpleUDP_common.h"
#include "MsgLogger.h"
#include <string>

extern SIMPLEUDP_API MsgLogger *pLogger;
extern SIMPLEUDP_API void Log(LPCTSTR fmt, ...);
extern SIMPLEUDP_API std::string ws2s(const std::wstring &wstr);
extern SIMPLEUDP_API std::wstring s2ws(const std::string &str);
extern SIMPLEUDP_API bool RandomBool(double truerate);

extern SIMPLEUDP_API double send_failrate;
extern SIMPLEUDP_API double send_waitrate;