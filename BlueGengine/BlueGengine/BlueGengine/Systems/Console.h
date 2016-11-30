#pragma once
#include "../Types.h"
#include <string>

namespace BlueGengine
{
	namespace Console
	{
		enum ELogType : uint8
		{
			Info,
			Error
		};
		void AddLogString(std::string aString, ELogType aLogType);

		void Init();
		void Update();

	}
}