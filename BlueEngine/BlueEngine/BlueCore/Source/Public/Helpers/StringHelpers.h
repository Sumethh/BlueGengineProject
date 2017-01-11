#pragma once
#include "Core/Types.h"
#include <string>
namespace BlueCore
{
	namespace StringHelpers
	{
		static inline uint32 FindCharacterCount(std::string& aString, char aSearchingChar)
		{
			uint32 count = 0;

			for (sizeInt i = 0; i < aString.size(); ++i)
			{
				if (aString[i] == aSearchingChar)
				{
					count++;
				}
			}

			return count;
		}
	}
}