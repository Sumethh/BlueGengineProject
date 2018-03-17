#include "BlueCore/Memory/TaggedBlockAllocator.h"
#include "BlueCore/Managers/MemoryManager.h"

namespace Blue
{
	thread_local byte* currentPage = nullptr;
	thread_local uint32 bytesAllocated = 0;

	TaggedBlockAllocator::TaggedBlockAllocator(uint64 aTag) : mTag(aTag)
	{

	}

	void* TaggedBlockAllocator::Allocate(uint32 aSize)
	{
		if (!currentPage || bytesAllocated + aSize > TaggedPageAllocator::sPageSize)
		{
			TaggedPageAllocator* pageAllocator = MemoryManager::GI()->GetTaggedPageAllocator();
			currentPage = static_cast<byte*>(pageAllocator->AllocatePage(mTag, currentPage));
		}
		void* memory = static_cast<void*>(currentPage + bytesAllocated);
		bytesAllocated += aSize;

		return memory;
	}

	void TaggedBlockAllocator::Free()
	{
		TaggedPageAllocator* pageAllocator = MemoryManager::GI()->GetTaggedPageAllocator();
		pageAllocator->DeallocateTag(mTag);
	}
}