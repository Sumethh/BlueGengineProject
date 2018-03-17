#pragma once
#include "TaggedPageAllocator.h"


namespace Blue
{
	class TaggedBlockAllocator
	{
		struct Block
		{

		};
	public:
		TaggedBlockAllocator(uint64 aTag);
		void* Allocate(uint32 aSize);
		void Free();
	private:	
		const uint64 mTag;
	};
}