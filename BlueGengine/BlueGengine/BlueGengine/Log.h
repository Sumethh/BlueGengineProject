#pragma once
#include <iostream>
namespace BlueGengine
{

#define LOGI(message) std::cout << "[Info] " << message << '\n';
	class Log
	{
		public:
		static void LogError(char* a_message)
		{
			std::cout << "ERROR: " << a_message << std::endl;
		}
	};
}

