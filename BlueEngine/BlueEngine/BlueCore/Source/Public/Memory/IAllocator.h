#pragma once

#include "Core/Types.h"
#include "Core/Defines.h"


namespace BlueCore
{
	class IAllocator
	{
		public:
		void* Allocate(sizeInt  aSize) = 0;
		void DeAllocate(sizeInt aSize) = 0;

		inline sizeInt Size() const  { return mSize; }
		inline sizeInt UsedMemory() const { return mUsedMemory; }
		inline sizeInt NumAllocations()const { return mNumAllocations; }

		inline void* Start() const { return mStart; }

		protected:
		void* mStart;
		sizeInt mSize;
		6

		sizeInt mNumAllocations;
		sizeInt mUsedMemory;
	};
}
