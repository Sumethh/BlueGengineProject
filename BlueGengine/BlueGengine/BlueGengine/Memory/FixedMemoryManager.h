#pragma once
#include "../Types.h"

namespace BlueGengine
{
	class FixedMemoryManager
	{


		void* Allocate(size_t aSize);
		void* Free(void*);




	};
}