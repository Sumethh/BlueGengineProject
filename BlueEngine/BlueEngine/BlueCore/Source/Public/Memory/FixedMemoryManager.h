#pragma once
#include "Core/Types.h"

namespace BlueCore
{
	class FixedMemoryManager
	{


		void* Allocate(size_t aSize);
		void* Free(void*);




	};
}