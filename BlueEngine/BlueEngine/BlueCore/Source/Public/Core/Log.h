#pragma once
#include <string>
#define LOGGING
#define VERBOSE_LOGGING 1

namespace BlueCore
{
	class Log
	{
		public:
		static void Init(char* aFileName);
		static void LogError(std::string aMessage);
		static void LogInfo(std::string aMessage);
		static void Flush();
	};
}

#if VERBOSE_LOGGING
#define Verbose_Log(message) do{ if(true) Log::LogInfo(message);}while(0)
#else
#define Verbose_Log(message) do{ if(false) Log::LogInfo(message);}while(0)
#endif