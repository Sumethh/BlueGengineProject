#pragma once
#include <iostream>
namespace BlueGengine
{

#define LOGI(message) std::cout << "[Info] " << message << '\n';
	class Log
	{
		public:
		static void LogError(char* aMessage)
		{
			std::cout << "ERROR: " << aMessage << std::endl;
		}
	};
}

