#include "BlueCore/Memory/TaggedPageAllocator.h"
#include "BlueCore/Core/Defines.h"

namespace Blue
{
	const int32 TaggedPageAllocator::sPageSize = 2000000;
	void* TaggedPageAllocator::AllocatePage(uint64 aTag, void* aReturningPage)
	{
		std::lock_guard<std::mutex> lock(mAllocationMutex);

		if (aReturningPage)
		{
			mAllocatedPages[aTag].emplace_back(aReturningPage);
		}

		void* returningPage = nullptr;
		
		if (!mFreePages.empty())
		{
			returningPage = mFreePages.front();
			mFreePages.pop();
		}
		else
		{
			void* newPage = malloc(sPageSize);
			BlueAssert(newPage);			
			returningPage = newPage;
		}

		return returningPage;
	}

	void TaggedPageAllocator::DeallocateTag(uint64 aTag)
	{
		std::lock_guard<std::mutex> lock(mAllocationMutex);

		auto foundIterator = mAllocatedPages.find(aTag);
		if (foundIterator != mAllocatedPages.end())
		{
			std::vector<void*>& listOfPages = foundIterator->second;
			for (void* page : listOfPages)
			{
				mFreePages.push(page);
			}
			listOfPages.clear();
		}
	}

}