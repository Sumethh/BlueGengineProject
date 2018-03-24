#pragma once
#include "BlueCore/Core/Types.h"

#include <map>
#include <queue>
#include <vector>
#include <mutex>

namespace Blue
{
	class TaggedPageAllocator
	{
	public:
		TaggedPageAllocator();
		~TaggedPageAllocator();

		void* AllocatePage(uint64 aTag, void* aReturningPage);
		void DeallocateTag(uint64 aTag);

		const static int32 sPageSize;
	private:
		std::mutex mAllocationMutex;

		std::map<uint64, std::vector<void*>> mAllocatedPages;
		std::queue<void*> mFreePages;

		uint32 mPagesTotal = 0;
		uint32 mPagesAllocated = 0;
		uint32 mPagesFree = 0;
		uint32 mMbytesTotal = 0;
		uint32 mMbytesUsed = 0;
		uint32 mMbFree = 0;
	};
}