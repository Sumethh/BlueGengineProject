#pragma once
#include "../Types.h"

namespace BlueGengine
{
	class FixedMemoryManager
	{


		void* Allocate(size_t a_size);
		void* Free(void*);




	};
}