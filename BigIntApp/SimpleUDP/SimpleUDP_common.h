#pragma once

#if defined(SIMPLEUDP_DLLEXPORT) && !defined(SIMPLEUDP_API)
#define SIMPLEUDP_API __declspec(dllexport)
#else
#define SIMPLEUDP_API __declspec(dllimport)
#endif
