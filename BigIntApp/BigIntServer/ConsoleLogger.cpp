#include "StdAfx.h"
#include "ConsoleLogger.h"

void ConsoleLogger::Log(LPCTSTR msg)
{
	_putts(msg);
}