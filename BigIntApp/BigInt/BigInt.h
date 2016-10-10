#pragma once

#if defined(BIGINT_DLLEXPORT) && !defined(BIGINT_API)
#define BIGINT_API __declspec(dllexport)
#else
#define BIGINT_API __declspec(dllimport)
#endif


#include <string>

BIGINT_API bool isnum(const std::string &s);
BIGINT_API std::string add(const std::string &a, const std::string &b);
BIGINT_API std::string sub(const std::string &a, const std::string &b);
BIGINT_API std::string mul(const std::string &a, const std::string &b);
BIGINT_API std::string div(const std::string &a, const std::string &b);
BIGINT_API int cmp(const std::string &a, const std::string &b);
