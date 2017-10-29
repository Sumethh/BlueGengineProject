#pragma once
#include "BlueCore/Core/Types.h"
#include <string>
#include <functional>

namespace Blue
{
	namespace Console
	{
		enum ELogType : uint8
		{
			Info,
			Warning,
			Error,
			Verbose
		};
		void AddLogString(std::string aString, ELogType aLogType);

		void AddCommand(std::string commandBase, std::function<void(std::string, std::string*, const uint32)> aCallBack);

		void Init();
		void Update();

		bool IsOpen();

	}
}