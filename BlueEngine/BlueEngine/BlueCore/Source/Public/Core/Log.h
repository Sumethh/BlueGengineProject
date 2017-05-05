#pragma once
#include "BlueCore.h"
#include <string>
#define LOGGING
#define VERBOSE_LOGGING 1


class Log
{
	public:
	static   void Init(char* aFileName);
	static   void Error(std::string aMessage);
	static   void Info(std::string aMessage);
	static   void Flush();
};

#if VERBOSE_LOGGING
	#define Verbose_Log(message) do{ if(true) Log::Info(message);}while(0)
#else
	#define Verbose_Log(message) do{ if(false) Log::Info(message);}while(0)
#endif