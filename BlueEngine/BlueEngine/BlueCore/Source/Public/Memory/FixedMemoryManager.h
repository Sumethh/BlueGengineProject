#pragma once
#include "Core/Types.h"


class FixedMemoryManager
{


	void* Allocate(size_t aSize);
	void* Free(void*);




};
