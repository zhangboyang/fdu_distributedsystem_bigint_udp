#pragma once
#include "MsgLogger.h"

class ConsoleLogger :
	public MsgLogger
{
public:
	virtual void Log(LPCTSTR msg);
};
