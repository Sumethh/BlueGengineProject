#pragma once
#include "BlueCore/Core/Types.h"

namespace Blue
{
#ifdef RELEASE
	#define DEBUG_MEMORY_ALLOCATION 0
#else
	#define DEBUG_MEMORY_ALLOCATION 1
#endif
	class IMemoryAllocator
	{
	public:

		IMemoryAllocator();
		virtual ~IMemoryAllocator();


		virtual void* Allocate(size_t  aSize, uint8 aAllignment) = 0;
		virtual void Deallocate(void* aData, size_t aSize) = 0;

		inline size_t UsedMemory() const
		{
			return mUsedMemory;
		}
		inline size_t NumAllocations()const
		{
			return mNumAllocations;
		}
		virtual int32 GetLargestAllocationSize()
		{
			return 0;
		}
	protected:
		sizeInt mNumAllocations;
		sizeInt mUsedMemory;
	};
}