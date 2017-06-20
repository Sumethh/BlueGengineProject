#include "Memory/IMemoryAllocator.h"

namespace Blue
{
	IMemoryAllocator::IMemoryAllocator(): mUsedMemory(0),	mNumAllocations(0)
	{

	}

	IMemoryAllocator::~IMemoryAllocator()
	{
		mNumAllocations = 0;
		mUsedMemory = 0;
	}
}