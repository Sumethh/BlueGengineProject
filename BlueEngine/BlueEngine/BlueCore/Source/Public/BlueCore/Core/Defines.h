#pragma once
//disable warnings on 255 char debug symbols
#pragma warning (disable : 4786)
//disable warnings on extern before template instantiation
#pragma warning (disable : 4231)

#include <assert.h>
#include <string.h>


#define BlueBit(n) 1 << n

#define BlueAssert(condition) assert(condition);

#define BlueStaticAssert(condition) static_assert(condition, "");


#define InvalidDefaultCase default:{assert(false);break;}
#define InvalidDefaultCaseExtraStep(extraStep) default:{extraStep;assert(false);break;}

#if 1
	#ifdef BLUECORE_EXPORT
		#define BLUECORE_API __declspec(dllexport)
		#define EXP_TEMPLATE
	#else
		#define BLUECORE_API __declspec(dllimport)
		#define EXP_TEMPLATE extern
	#endif
#else
	#ifdef BLUECORE_EXPORT
		#define BLUECORE_API
		#define EXP_TEMPLATE
	#else
		#define BLUECORE_API
		#define EXP_TEMPLATE extern
	#endif
#endif

#define __FILENAME__ (strrchr(__FILE__, '/') ? strrchr(__FILE__, '/') + 1 : __FILE__)