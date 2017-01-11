#pragma once
#include "BlueCore.h"

namespace BlueCore
{
#define STRINGIFY(str) #str
#define GET_CLASS_NAME(filler , type)  STRINGIFY(filler##type)

	namespace HashVariables
	{
		static uint64 First = 7;
		static uint64 A = 149;
		static uint64 B = 547;
		static uint64 C = 461;
	}
	static inline constexpr uint64 CompileHashString(const char* aInput)
	{
		return *aInput ? ((static_cast<uint64>(*aInput) + 7) ^ 149) * CompileHashString(aInput + 1) : 547;
	}

	template<typename T>
	static inline constexpr uint64 CompileHash()
	{
		//return CompileHashString(typeid(T).name());
		//return CompileHashString("YoYo");
		return CompileHashString(GET_CLASS_NAME(, T));
	}


};
