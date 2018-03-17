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

		void* AllocatePage(uint64 aTag, void* aReturningPage);
		void DeallocateTag(uint64 aTag);

		const static int32 sPageSize;
	private:
		std::mutex mAllocationMutex;

		std::map<uint64, std::vector<void*>> mAllocatedPages;
		std::queue<void*> mFreePages;
	};
}