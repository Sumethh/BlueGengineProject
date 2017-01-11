#pragma once
#include <assert.h>
#define BlueBit(n) 1 << n



#define BlueAssert(condition) assert(condition);

#ifdef BLUECORE_EXPORT
	#define BLUECORE_API __declspec(dllexport)
#else
	#define BLUECORE_API __declspec(dllimport)
#endif
