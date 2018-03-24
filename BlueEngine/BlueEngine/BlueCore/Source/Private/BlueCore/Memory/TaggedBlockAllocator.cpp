#include "BlueCore/Memory/TaggedBlockAllocator.h"
#include "BlueCore/Managers/MemoryManager.h"

#include <map>
namespace Blue
{
	thread_local static std::map<uint64, byte*> currentPage;
	thread_local std::map<uint64, uint32> bytesAllocated;

	TaggedBlockAllocator::TaggedBlockAllocator(uint64 aTag) : mTag(aTag)
	{
		
	}

	void* TaggedBlockAllocator::Allocate(uint32 aSize)
	{
		byte* page = currentPage[mTag];
		uint32 bytes = bytesAllocated[mTag];
		if (!page || bytes + aSize >= static_cast<uint32>(TaggedPageAllocator::sPageSize))
		{
			TaggedPageAllocator* pageAllocator = MemoryManager::GI()->GetTaggedPageAllocator();
			page = static_cast<byte*>(pageAllocator->AllocatePage(mTag, page));
			bytesAllocated[mTag] = 0;
			currentPage[mTag] = page;
		}
		void* memory = static_cast<void*>(page + bytes);
		bytesAllocated[mTag] += aSize;

		return memory;
	}

	void TaggedBlockAllocator::Free()
	{
		TaggedPageAllocator* pageAllocator = MemoryManager::GI()->GetTaggedPageAllocator();
		pageAllocator->DeallocateTag(mTag);
	}
}