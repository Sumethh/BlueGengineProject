#pragma once
#include "BlueCore.h"


namespace Blue
{
	namespace HashVariables
	{
		static uint64 First = 7;
		static uint64 A = 149;
		static uint64 B = 547;
		static uint64 C = 461;
	}

	static inline constexpr uint64 CompileHash(char* aInput)
	{
		return *aInput ? ((static_cast<uint64>(*aInput) + 7) ^ 149) * CompileHash(aInput + 1) : 547;
	}
}