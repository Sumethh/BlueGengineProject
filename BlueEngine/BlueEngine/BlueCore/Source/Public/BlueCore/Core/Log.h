#pragma once
#include "BlueCore/BlueCore.h"
#include <string>
#include "Logger.h"
#define LOGGING
#define VERBOSE_LOGGING 1


namespace Blue
{
	class Log
	{
	public:
		static void Init(char* aFileName);
		static void Error(Logger aMessage);
		static void Warning(Logger aMessage);
		static void Info(Logger aMessage);
		static void Flush();
	};
}
#if VERBOSE_LOGGING
	#define Verbose_Log(message) do{ if(true) Blue::Log::Info(message);}while(0)
#else
	#define Verbose_Log(message) do{ if(false) Blue::Log::Info(message);}while(0)
#endif